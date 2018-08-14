ip link set dev tap0 up
ip address add dev tap0 10.0.0.0
route add -net 10.0.0.0 netmask 255.255.255.0 dev tap0
ip route delete 10.0.0.0 dev tap0 table local
