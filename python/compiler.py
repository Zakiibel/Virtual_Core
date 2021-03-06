#!/bibn/python3


import sys

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
        print(iv +" :Immidiate value out of [-128;127]")
        quit()



#split instruction to blocs
def splitCode(instr):
    bcc = "0000"
    flag = "0000"
    opcode = "0000"
    ope1 = "0000"
    ope2 = "0000"
    dest = "0000"
    iv = "0000"*2
    instr = instr.upper()
    blocs = instr.split(" ")    #string to list
    if len(blocs)==1:           #HALT
        opcode = "1011"

    elif len(blocs) == 2 :        #BCC
        iv = immValue(blocs[1])
        if (blocs[0])=="B" :
            bcc = "1000"
        elif blocs[0] == "BEQ" :
            bcc = "1001"
        elif blocs[0] == "BNE" :
            bcc = "1010"
        elif blocs[0] == "BLE" :
            bcc = "1011"
        elif blocs[0] == "BGE" :
            bcc = "1100"
        elif blocs[0] == "BL" :
            bcc = "1101"
        elif blocs[0] == "BG" :
            bcc = "1110"
        else :
            print("BCC code Incorrect")
            print(instr+"\n")
            quit()


    elif len(blocs) == 3 :   #MOV & CMP
        if blocs[0]=="MOV":
            opcode = "1000"
            dest = immValue(blocs[1][1:-1],4)
            if blocs[2][0]=='R':
                ope1= immValue(blocs[2][1:],4)
            else:
                flag = "0001"
                iv = immValue(blocs[2])

        elif blocs[0]=="CMP":
            opcode = "0101"
            ope1 = immValue(blocs[1][1:-1],4)
            if blocs[2][0]=='R':
                ope2 = immValue(blocs[2][1:],4)

            else:
                flag = "0001"
                iv = immValue(blocs[2])
        else :
            print("OPCODE Incorrect")
            print(instr+"\n")
            quit()



    elif len(blocs) == 4 :   #AND, ORR, EOR, ADD, ADC, SUB, SBC, LSH, RSH
        dest = immValue(blocs[1][1:-1],4)
        ope1 = immValue(blocs[2][1:-1],4)
        if blocs[3][0]=='R':
            ope2 = immValue(blocs[3][1:],4)
        else:
            flag = "0001"
            iv = immValue(blocs[3])

        if blocs[0]=="AND":
            opcode = "0000"
        elif blocs[0]=="ORR":
            opcode = "0001"
        elif blocs[0]=="EOR":
            opcode = "0010"
        elif blocs[0]=="ADD":
            opcode = "0011"
        elif blocs[0]=="ADC":
            opcode = "0100"
        elif blocs[0]=="SUB":
            opcode = "0110"
        elif blocs[0]=="SBC":
            opcode = "0111"
        elif blocs[0]=="LSH":
            opcode = "1001"
        elif blocs[0]=="RSH":
            opcode = "1010"
        else:
            print("OPCODE Incorrect")
            print(instr+"\n")
            quit()

    else:
        print("Error : instructions contains unvalid number of arguments")
        print(instr+"\n")
        quit()

    return bcc+flag+opcode+ope1+ope2+dest+iv+"\n"

#Open asm File and get the instructions
with open("/home/kali/Documents/carte a puce/Projet/v2/assembly/"+sys.argv[1],"r") as asmFile:
    instructions = asmFile.readlines()
    asmFile.close()


with open("/home/kali/Documents/carte a puce/Projet/v2/bin/"+sys.argv[2],"w") as code:
    for e in instructions:
        code.writelines(splitCode(e[:-1]))
    code.close()
