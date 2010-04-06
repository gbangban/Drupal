The FlashVideo Streaming module/plugin allows for FlashVideo video files to be stored on an external
streaming (RTMP) server such as Flash Media Server.

The Streaming module was designed by Mark W. Jarrell (attheshow) at
Jones Knowledge Group (http://www.jones.com).


Install
-------
Installing the FlashVideo Streaming module:

1) Copy the flashvideo_streaming folder to the "plugins" folder inside of the "flashvideo" module
folder in your installation.

2) Enable the module using Administer -> Modules (/admin/build/modules)

3) Visit the FlashVideo Universal Settings administration page (admin/settings/flashvideo/universal)

4) Enter in details for your "Streaming Server Configuration"

5) Under the "Flash Player Settings" section, add your "Streaming URL"
*Note: The streamer URL should begin with rtmp:// and include the streaming path to where your video files are
being saved on the streaming server.

6) Save the settings and you should be ready to upload and stream videos.

HOW TO: Configure OpenSSH Public / Private Keys
-------

Let's say we want to ssh from Ooga to Booga. As long as Ooga and Booga both run the same
implementation of OpenSSH, then it's easy. My particular situation is that my streaming server
is running Windows Server 2003 with the Cygwin tools and OpenSSH.

~~~~~~~~~~
ssh2: Ooga = OpenSSH, Booga = OpenSSH
~~~~~~~~~~
First, generate a public/private DSA key pair on Ooga (you will probably need to log in with the www-user
account to set this up correctly).

ooga $ ssh-keygen -t dsa -f ~/.ssh/id_dsa

When you are asked for a passphrase, leave it empty. Now send the public key to Booga.

ooga $ cd .ssh
ooga $ scp id_dsa.pub user@booga:~/.ssh

Next, log in to Booga and add the public key to the list of authorized keys.

ooga $ ssh user@booga

booga $ cd .ssh
booga $ cat id_dsa.pub >> authorized_keys2
booga $ chmod 640 authorized_keys2
booga $ rm -f id_dsa.pub

*Note that the filename may either be "authorized_keys2" or "authorized_keys" depending on your setup.
That's it; you're ready to ssh from Ooga to Booga without having to enter a password.


Support
-------
If you experience a problem with the module, file a
request or issue on the FlashVideo queue (http://drupal.org/project/issues/flashvideo).
DO NOT POST IN THE FORUMS. Posting in the issue queues
is a direct line of communication with the module author.