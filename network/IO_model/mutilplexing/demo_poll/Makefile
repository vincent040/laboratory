all:demo_poll_srv demo_poll_cli

demo_poll_srv:demo_poll_srv.c wrap.c
	gcc $^ -o $@ -lnetlib 

demo_poll_cli:demo_poll_cli.c  wrap.c
	gcc $^ -o $@ -lnetlib 

clean:
	rm demo_poll_srv demo_poll_cli
