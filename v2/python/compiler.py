#!/bibn/python3

#return binary representation of immidiate value
def immValue(iv,bits=8):
    intVlaue = int(iv)
    if intVlaue>=-(2**(bits-1)) and intVlaue<(2**(bits-1)):
        if intVlaue > 0:
            strValue = bin(intVlaue)[2:]
            value = "0"*(bits-len(strValue)) + strValue
        elif intVlaue < 0:
            value = bin(((-intVlaue)^0xff) +1)[2:][8-bits:]
        else :
            value = "0"*bits
        return value
    else :
        return (iv+" :Immidiate value out of [-128;127]")

def affect(str1,str2,i,j):
    return str1[:i] + str2+ str1[j:]

#split instruction to blocs
def splitCode(instr):
    #instrBin = "0"*32
    bcc = "0000"
    flag = "0000"
    opcode = "0000"
    ope1 = "0000"
    ope2 = "0000"
    dest = "0000"
    iv = "0000"*2
    blocs = instr.split(" ")    #string to list
    if len(blocs)==1:           #HALT
        #instrBin = affect(instrBin,"1011",8,12)
        opcode = "1011"

    elif len(blocs) == 2 :        #BCC
        if blocs[0]=="B" :
            pass
        elif blocs[0] == "BEQ" :
            pass
        elif blocs[0] == "BNE" :
            pass
        elif blocs[0] == "BLE" :
            #instrBin = affect(instrBin,"1011",0,4)
            bcc = "1011"
            #instrBin = affect(instrBin,immValue(blocs[1]),24,32)
            iv = immValue(blocs[1])


        elif blocs[0] == "BGE" :
            pass
        elif blocs[0] == "BL" :
            pass
        elif blocs[0] == "BG" :
            pass


    elif len(blocs) == 3 :   #MOV & CMP
        if blocs[0]=="MOV":
            opcode = "1000" #instrBin = affect(instrBin,"1000",8,12)
            dest = immValue(blocs[1][1:-1],4) #instrBin = affect(instrBin,immValue(blocs[1][1:-1],4),20,24)
            if blocs[2][0]=='r':
                #instrBin[12:16]
                ope1= immValue(blocs[2][1:],4)
            else:
                flag = "0001"
                #instrBin[-8:]
                iv = immValue(blocs[2])

        elif blocs[0]=="CMP":
            #instrBin[8:12]
            opcode = "0101"
            #instrBin[12:16]
            ope1 = immValue(blocs[1][1:-1],4)
            if blocs[2][0]=='r':
                #instrBin[16:20]
                ope2 = immValue(blocs[2][1:],4)
            else:
                flag = "0001"
                #instrBin[-8:]
                iv = immValue(blocs[2])



    elif len(blocs) == 4 :   #AND, ORR, EOR, ADD, ADC, SUB, SBC, LSH, RSH
        #instrBin[20:24]
        dest = immValue(blocs[1][1:-1],4)
        #instrBin[12:16]
        ope1 = immValue(blocs[2][1:-1],4)
        if blocs[3][0]=='r':
            #instrBin[16:20]
            ope2 = immValue(blocs[3][1:],4)
        else:
            flag = "0001"
            #instrBin[-8:]
            iv = immValue(blocs[3])

        if blocs[0]=="ADD":
            #instrBin[8:12]
            opcode = "0011"

    else:
        print("Error : instructions contains unvalid number of arguments")

    return bcc+flag+opcode+ope1+ope2+dest+iv+"\n"

#Open asm File and get the instructions
with open("/home/kali/Documents/carte a puce/Projet/v2/sources/asm.s","r") as asmFile:
    instructions = asmFile.readlines()
    asmFile.close()


with open("/home/kali/Documents/carte a puce/Projet/v2/sources/code1","w") as code:
    for e in instructions:
        instr = e[:-1]
        line = splitCode(instr)
        code.writelines(line)
    code.close()
