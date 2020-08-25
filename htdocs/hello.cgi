#!/usr/bin/env python3
import cgi, cgitb

form = cgi.FieldStorage()
name = form.getvalue('NAME')

s = '''
<html>
<head></head>
<body>
hello CGI, {}
</body>
</html>
'''.format(name)

print(s)
