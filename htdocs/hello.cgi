#!/usr/bin/env python3
import cgi, cgitb

form = cgi.FieldStorage()
name = form.getvalue('NAME')

if not name:
    name = 'Oh, no'

if name == 'NCtfU':
    name = "<URL>"
elif len(name) > 1000:
    name = "Stop, What did you find?"
elif len(name) > 500:
    name = "U"
elif len(name) > 400:
    name = "f"
elif len(name) > 300:
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
