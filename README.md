# network-cat

Like `cat`, but on network dude.

![network cat](http://alexdantas.net/projects/network-cat/images/cat-at-laptop.jpg)

You can transfer files over the network with it.

## Usage

To start the server and listen to files:

    $ network-cat -L [port]       # defaults to 27015

It just waits for incoming files. To exit, either
`kill` or interrupt it (Ctrl+C).

You need to tell your IP to the clients, so on the server side do
this:

    $ ip a | grep 'inet '

Then, startup the client.

    $ small-talk host-ip [port]   # also defaults to 27015

Then you can type anything and it'll be echoed back to the server.
It reads from standard input and finished on an end-of-file
(EOF, Ctrl+D). Multiple clients can do this at the same time.

To send files, pipe the output into the client:

    $ cat some-file.txt | network-cat 132.231.23.212   # example ip

## Development

It uses UDP sockets to transfer info between client and server.

The code tried to be as modular as possible, although there may be some
ugly fixes.

C++ rules but Ruby ownz.

## Credits

Don't take this project too seriously, it was made as an assignment
on a Networking class.

It was made by Alexandre Dantas on a rainy afternoon.

* [GitHub](https://github.com/alexdantas)
* [Website](http://alexdantas.net/)

<!-- Ignore the following if viewing on text mode -->
[![emacs banner](http://badges.alexdantas.net/emacs.png)](http://badges.alexdantas.net/)

