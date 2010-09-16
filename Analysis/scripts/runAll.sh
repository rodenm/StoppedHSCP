
# background ICHEP

python StoppedHSCP/Analysis/python/runAnalysis.py Comm10_May6th_cl_v4 1044,1045,1046,1047,1049,1058,1059,1089,1090,1101,1104,1107 json_BG_v0.txt

# background w std JSON (Jun14th)

python StoppedHSCP/Analysis/python/runAnalysis.py Comm10_Jun14th_v2_CAF 1044,1045,1046,1047,1049,1058,1059,1089,1090,1101,1104,1107 json_Jun14th_133320_135575.txt

# background w std JSON (SE)

python StoppedHSCP/Analysis/python/runAnalysis.py Comm10_Jun14th_v3_RAL 1044,1045,1046,1047,1049,1058,1059,1089,1090,1101,1104,1107 json_newBG.txt


# ICHEP search

python StoppedHSCP/Analysis/python/runAnalysis.py Run2010A_May27th_cl_v1 1117,1118,1119,1121,1122 json_Search_v0.txt

python StoppedHSCP/Analysis/python/runAnalysis.py Run2010A_Promptv6_v8 1179,1182,1185,1186,1188,1190,1192,1196,1197,1198,1199 json_Search_v6.txt

python StoppedHSCP/Analysis/python/runAnalysis.py Run2010A_Jul16th_v1 1207,1222,1224,1225,1226 json_Search_v6_Jul16th.txt


# ICHEP search w std JSONs

# replacement for May27th_cl_v1 missing !

python StoppedHSCP/Analysis/python/runAnalysis.py Run2010A_Promptv6_v18 1179,1182,1185,1186,1188,1190,1192,1196,1197,1198,1199 json_3Sep_138560-139459.txt 

python StoppedHSCP/Analysis/python/runAnalysis.py Run2010A_Jul16th_v2 1207,1222,1224,1225,1226 json_3Sep_139779_140182.txt 


# newer data

python StoppedHSCP/Analysis/python/runAnalysis.py Run2010A_Promptv6_v16 1229,1232,1233,1250  json_27Aug_140331_141882.txt

python StoppedHSCP/Analysis/python/runAnalysis.py Run2010A_Promptv6_v11 1251 json_Search_v8.txt

python StoppedHSCP/Analysis/python/runAnalysis.py Run2010A_Promptv6_v12 1253,1256,1257,1258,1260,1262,1263,1264,1266,1267,1268,1271 json_25Aug_142035_142664.txt

python StoppedHSCP/Analysis/python/runAnalysis.py Run2010A_Promptv6_v14 1264,1266,1267,1268,1271 json_25Aug_142461_142664.txt

python StoppedHSCP/Analysis/python/runAnalysis.py Run2010A_Promptv6_v13 1283,1284,1285,1287 json_20Aug10_142665_143179.txt

python StoppedHSCP/Analysis/python/runAnalysis.py Run2010A_Promptv6_v15 1293,1295 json_27Aug_143179_143336.txt 

python StoppedHSCP/Analysis/python/runAnalysis.py Run2010A_Promptv6_v17 1298,1299,1301,1303,1305,1308,1309 json_3Sep_143657_144114.txt