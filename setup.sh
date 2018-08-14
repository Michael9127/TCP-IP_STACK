ip link set dev tun0 up
ip address add dev tun0 10.0.0.0
route add -net 10.0.0.0 netmask 255.255.255.0 dev tun0
ip route delete 10.0.0.0 dev tun0 table local
