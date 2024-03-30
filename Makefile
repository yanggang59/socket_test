all:
	make -C tcp
	make -C udp

clean:
	@rm tcp/tcp_server tcp/tcp_client -rf
	@rm udp/udp_server udp/udp_client -rf