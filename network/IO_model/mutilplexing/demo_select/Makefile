all:demo_select_srv demo_select_cli

demo_select_srv:demo_select_srv.c 
	gcc demo_select_srv.c -o demo_select_srv -lnetlib 

demo_select_cli:demo_select_cli.c 
	gcc demo_select_cli.c -o demo_select_cli -lnetlib 

clean:
	rm demo_select_srv demo_select_cli
