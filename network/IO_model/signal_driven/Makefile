all:udp_srv udp_cli

udp_srv:udp_srv.c
	gcc $^ -o $@ -lnetlib

udp_cli:udp_cli.c
	gcc $^ -o $@ -lnetlib

clean:
	rm -rf udp_cli udp_srv
