import xml.etree.ElementTree as ET

tree = ET.parse('mwe.xml')

mwegroups = tree.findall('mwegroup')

lista = []

for group in mwegroups:
 insta = group.find('instances')
 for mwe in insta:
  strink = ''
  for var in mwe:
   strink += u' ' + unicode(var.text)
  lista.append(strink)
  if group.get('type') == 'flex':
   strink = ''
   for var in reversed(mwe):
    strink += u' ' + unicode(var.text)
   lista.append(strink)

f = open('mwe.txt','wb')
for linia in lista:
 f.write(linia.strip().encode('utf8') + '\n')
f.close()

