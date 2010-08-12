#utility to generate lumi_record.txt formatted output from Lumi csv file

import re

goodRange = re.compile(r'^(\d*):(\d*)-\d*:(\d*)')
goodLine = re.compile(r'^\s*(\d*),\s*(\d*),\s*\d*,\s*\d*,\s*[0-9e+-.]*,\s*([0-9e+-.]*)')

start_run = 136035
end_run   = 136082

ranges = (
#    '133874:1-133874:814',
#    '133874:817-133874:875',
#    '133875:1-133875:20',
#    '133875:22-133875:49',
#    '133876:1-133876:330',
#    '133877:1-133877:77',
#    '133877:82-133877:231',
#    '133877:236-133877:1640',
#    '133877:1643-133877:1997',
#    '133881:1-133881:71',
#    '133881:74-133881:223',
#    '133881:225-133881:562',
#    '133885:1-133885:794',

    '136035:1-136035:53',
    '136035:55-136035:207',
    '136035:209-136035:259',
    '136066:67-136066:109',
    '136066:112-136066:143',
    '136066:145-136066:297',
    '136066:299-136066:348',
    '136066:350-136066:529',
    '136066:532-136066:595',
    '136066:597-136066:1184',
    '136080:182-136080:262',
    '136082:1-136082:506',
    '136087:78-136087:141',
    '136087:144-136087:354',
    '136088:1-136088:262',    
    '136097:1-136097:91',
    '136098:1-136098:25',
    '136100:1-136100:94',
    '136119:1-136119:36',
    )

rs = []

for line in ranges:
    range = goodRange.match(line)
    if (range):
        rs.append({'run' : range.group(1),
                   'low' : int(range.group(2)),
                   'high': int(range.group(3))})

f = open("lumi_by_LS_all.csv")
for line in f.readlines():
    m = goodLine.match(line)
    ok = False
    if (m
        and int(m.group(1)) >= start_run
        and int(m.group(1)) <= end_run):
        for r in rs:
            if (m.group(1) == r['run']
                and int(m.group(2)) >= r['low']
                and int(m.group(2)) <= r['high']):
                print m.group(1), m.group(2), m.group(3), 1
                ok = True
        if (not ok):
            print m.group(1), m.group(2), m.group(3), 0
