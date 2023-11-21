class Pass1:
    def __init__(self) -> None:
        self.count_pp =0
        self.count_kp =0
        self.kptp = 1
        self.mdtp =1
        self.macro_count = 0
        self.pntab = ""
        self.mdt = ""
        self.kpdt = ""
        self.mnt = ""
        self.ic = ""
        pass
    
    def process(self):
        NEXT_MACRO = False
        IS_START = False
        with open("D:\Java Projects\TE-Assignments\MacroAssembler\input.txt", "r") as file:
            data = file.readlines()
            for lines in data:
                if lines.find("START") != -1 or IS_START == True:
                    self.ic+=lines
                    IS_START= True
                else:
                    word = lines.replace("&","").replace(",","").split()
                    if NEXT_MACRO == True:
                        self.count_kp =0
                        self.count_pp = 0
                        macro_name = word[0]
                        self.pntab += f"{macro_name}"+"\t"
                        for i in range(1,len(word)):
                            if word[i].find("=") != -1 :
                                self.count_kp+=1
                                parameter_name = word[i].partition("=")[0]
                                given_name = word[i].partition("=")[2]
                                self.pntab += f"{parameter_name}\t"
                                self.kpdt += f"{parameter_name}\t{given_name}\n"
                            else:
                                self.count_pp+=1   
                                self.pntab+= word[i]+"\t"
                        self.pntab+= "\n"        
                        self.mnt += f"{macro_name}\t{self.count_kp}\t{self.count_pp}\t{self.kptp}\t{self.mdtp}\n"
                        self.kptp+=self.count_kp
                        NEXT_MACRO = False
                    elif word[0] == 'MACRO':
                        self.macro_count +=1
                        NEXT_MACRO = True
                        pass
                    else:
                        string = word[0] + "\t"
                        parameters = self.pntab.split('\n')[self.macro_count-1].split()
                        # print(parameters)
                        for i in range(1,len(word)):
                            if word[i].find("=") != -1:
                                string += word[i]+"\t"
                            else:
                                index = parameters.index(word[i])  
                                string += f"(P,{index})\t"
                        self.mdtp+=1
                        string+="\n"
                        self.mdt += string                     
        with open('MDT.txt', 'w') as file:
            file.write(self.mdt)

        # Write MNT to a file
        with open('MNT.txt', 'w') as file:
            file.write(self.mnt)

        # Write PNTAB to a file
        with open('PNTAB.txt', 'w') as file:
            file.write(self.pntab)

        # Write KPDT to a file
        with open('KPDT.txt', 'w') as file:
            file.write(self.kpdt)

        
test = Pass1()
test.process()        
        