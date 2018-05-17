#include "head4player.h"

int sfd; 

int getsfd()
{
	return sfd;
}

enum mad_flow input(void *data, struct mad_stream *stream)     
{     
    struct buffer *buffer = data;     
    if(buffer->length == 0)
    {
        return MAD_FLOW_STOP;     
    }

    mad_stream_buffer(stream, buffer->start, buffer->length);     

    buffer->length = 0;     
    return MAD_FLOW_CONTINUE;     
}     

int scale(mad_fixed_t sample)     
{     
    sample += (1L << (MAD_F_FRACBITS - 16));     

    if (sample >= MAD_F_ONE)     
    {
        sample = MAD_F_ONE - 1;     
    }
    else if (sample < -MAD_F_ONE)     
    {
        sample = -MAD_F_ONE;     
    }

    return sample >> (MAD_F_FRACBITS + 1 - 16);     
}     

enum mad_flow output(void *data,
                     struct mad_header const *header,
                     struct mad_pcm *pcm)     
{     
    unsigned int nchannels, nsamples, n;     
    mad_fixed_t const *left_ch, *right_ch;     
    unsigned char Output[6912], *OutputPtr;     
    int fmt, wrote, speed;     
        
    nchannels = pcm->channels;     
    n = nsamples = pcm->length;     
    left_ch = pcm->samples[0];     
    right_ch = pcm->samples[1];     
        
    fmt = AFMT_S16_LE;     
    speed = pcm->samplerate * 2;
    ioctl(sfd, SNDCTL_DSP_SPEED, &(speed));     
    ioctl(sfd, SNDCTL_DSP_SETFMT, &fmt);     
    ioctl(sfd, SNDCTL_DSP_CHANNELS, &(pcm->channels));     
    OutputPtr = Output;     

    while(nsamples--)
    {     
        signed int sample;     
        sample = scale(*left_ch++);     
        *(OutputPtr++) = sample >> 0;     
        *(OutputPtr++) = sample >> 8;     

        if(nchannels == 2)
        {     
            sample = scale(*right_ch++);     
            *(OutputPtr++) = sample >> 0;     
            *(OutputPtr++) = sample >> 8;     
        }     
    }     

    n *= 4;
    OutputPtr = Output;     
    while(n > 0)
    {     
        wrote = write(sfd, OutputPtr, n);     
        OutputPtr += wrote;     
        n -= wrote;     
    }     
    OutputPtr = Output;     

    return MAD_FLOW_CONTINUE;     
}     
        
enum mad_flow error(void *data,     
                    struct mad_stream *stream,
                    struct mad_frame *frame)     
{     
    return MAD_FLOW_CONTINUE;     
}     
        
int decode(unsigned char const *start, unsigned long length)     
{     
	if ((sfd = open("/dev/dsp", O_WRONLY)) < 0)
    {
        printf("can not open device!!!/n");     
        exit (-1);     
    }

    ioctl(sfd, SNDCTL_DSP_SYNC, 0); 
    struct buffer buffer;     
    struct mad_decoder decoder;     
    int result;     
    buffer.start = start;     
    buffer.length = length;     

    mad_decoder_init(&decoder, &buffer, input, NULL, NULL, output, error, NULL);     
    mad_decoder_options(&decoder, 0);     

    result = mad_decoder_run(&decoder, MAD_DECODER_MODE_SYNC);     
	close(sfd);
    mad_decoder_finish(&decoder);     

    return result;     
}
