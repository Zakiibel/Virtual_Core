with open("sources/code1","r") as code1F, open("sources/code","r") as codeF, open("sources/asm.s") as asmF:
    code = codeF.readlines()
    code1 = code1F.readlines()
    asm = asmF.readlines()
    asmF.close()
    codeF.close()
    code1F.close()

for i in range(len(code)):
    if(code[i]==code1[i]):
        print("Line %s : True"%(i+1))
    else:
        print("Line %s : False"%(i+1))
        print(asm[i][:-1])
        print(code[i][:-1])
        print(code1[i])
