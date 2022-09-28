import re
import sys

title = r'\\title'
section = r'\\section'
subsection = r'\\subsection'
begin = r'\\begin{itemize}'
item = r'\\item'
end = r'\\end{itemize}'
flag = 0
file = open("input1", "r")

for linha in file:
    m = re.sub(title, "#", linha)
    m = re.sub(section, "##", m)
    m = re.sub(subsection, "###", m)

    p = re.search(begin,linha)
    q = re.search(end,linha)

    if p: flag = 1
    elif q: flag = 0
    elif flag == 1:
        m = re.sub(item,'-',linha)
        print(m)
    else: print(m)
file.close()