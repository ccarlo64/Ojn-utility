utility to read accounts files created with openjabnab

instructions for compile:
into the server with openjabnab installed (qt4)

qmake -r
make

use:
ojnra account_filename

or

ojnra new

will create sysadm.dat width file user account: sysadm and password: sysadm


remember to change the permissions of the file with 
chmod 777 sysadm sysadm.dat
