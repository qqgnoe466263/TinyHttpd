#!/usr/bin/env python3
import cgi, cgitb

form = cgi.FieldStorage()
name = form.getvalue('NAME')

if not name:
    name = 'Oh, no'

if name == 'NCtfU':
    name = "To find the pikachu.png!"
elif len(name) > 500:
    name = "U"
elif len(name) > 200:
    name = "f"
elif len(name) > 200:
    name = "t"
elif len(name) > 200:
    name = "C"
elif len(name) > 100:
    name = "N"
elif len(name) > 50:
    name = "You need to input as same as pwn"

s = '''
<html>
<head></head>
<body>
{}
</body>
</html>
'''.format(name)

print(s)