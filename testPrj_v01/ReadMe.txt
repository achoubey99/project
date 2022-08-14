Compile code in the following way


#Server

$g++ MainServer.cpp Server.cpp -o s


#Client

$g++ -g MainClient.cpp Client.cpp -pthread -o c


And Run first the server as

$./s

and then client

$./c


