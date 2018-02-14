import xml.etree.ElementTree as ET

tree = ET.parse('mwe_complex-patterns.xml')

mwegroups = tree.findall('mwegroup')

lista = []

for group in mwegroups:
 insta = group.find('instances')
 for mwe in insta:
  strink = ''
  for var in mwe.findall('var'):
   strink += u' ' + unicode(var.text)
  lista.append(strink)
  if group.get('type') == 'flex':
   strink = ''
   for var in reversed(mwe.findall('var')):
    strink += u' ' + unicode(var.text)
   lista.append(strink)

f = open('mwe2.txt','wb')
for linia in lista:
 f.write(linia.strip().encode('utf8') + '\n')
f.close()

