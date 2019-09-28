# OpenRdate

#### openrdate - set the system's date from a remote host

## Help this project ##

openrdate needs your help. **If you are a programmer** and if you wants to help
a nice project, this is your opportunity.

openrdate was imported from some tarballs (the original homepage[1] and
developers are inactive). After this, all patches found in Debian project and
other places for this program were applied. All initial work was registered in
ChangeLog file (version 1.10 and later releases). openrdate is being packaged
in Debian[2] Project.

If you are interested to help openrdate, read the [CONTRIBUTING.md](CONTRIBUTING.md) file.

[1]: https://sourceforge.net/projects/openrdate
[2]: https://tracker.debian.org/pkg/openrdate

## What is OpenRdate? ##

OpenRdate or openrdate or rdate displays and sets the local date and time from
the host name or address given as the argument. The time source may be an RFC
868 TCP protocol server, which is usually implemented as a built-in service of
inetd(8), or an RFC 5905 protocol SNTP/NTP server. By default, rdate uses the
RFC 868 TCP protocol.

OpenRdate supports IPv4 and IPv6 protocols.

OpenRdate was originally developed by David Snyder and was based in rdate,
created by Christos Zoulas in 1994 for OpenBSD Project. Over time, OpenRdate
got several contributions from people. Please, see AUTHORS and HISTORY files
in source code  for more details.

## Build and Install ##

OpenRdate depends of libbsd[3] to build.

[3]: https://libbsd.freedesktop.org/wiki/

To build and install, run the following commands:

    $ ./autogen.sh
    $ ./configure
    $ make
    # make install

To return to original source code you can use '$ make distclean' command.

On Debian systems you can use '# apt install rdate'.

## How to set a time server in Debian ##

For test purposes, you can set your own time server. However, how to make it
will depend of your system. For Debian systems, you can set it easily.

### For time protocol (RFC 868, port 37 TCP/UDP): ###

    # apt-get install xinetd
    # nano /etc/xinetd.d/time

Change the lines:

    disable = yes

to

    disable = no

Restart the xinetd daemon:

    # systemctl restart xinetd

Verify the open ports:

    # ss -tunlp

Test rdate:

    # rdate <server_ip>

### For SNTP protocol (RFC 5905, port 123 UDP) ###

You can set a SNTP server using several available options. However, there are
lot of public servers on Internet. So, you can use:

    # rdate -n pool.ntp.org

## Author ##

OpenRdate was originally developed by David Snyder under BSD-4-Clause license.

Currently, the source code and newer versions are available at
https://github.com/resurrecting-open-source-projects/openrdate
