from modules.sound import sound
import serial
# print('serial ' + serial.__version__)

# Set a PORT Number & baud rate
PORT = '/dev/cu.usbmodem141301'
BaudRate = 9600

ARD= serial.Serial(PORT,BaudRate)

def Decode(A):
    A = A.decode()
    A = str(A)
    if A[0]=='S':                       #첫문자 검사
        if (len(A)==8):                #문자열 갯수 검사
            SoundPlay=int(A[5])
            result = SoundPlay
            return result
        else : 
            print ("Error_lack of number _ %d" %len(A))
            return False
    else :
        print ("Error_Wrong Signal")
        return False
    
def Ardread(): # return list [Ard1,Ard2]
        if ARD.readable():
            LINE = ARD.readline()
            code=Decode(LINE) 
            print(code)
            return code
        else : 
            print("읽기 실패 from _Ardread_")


while (True):
    SoundPlay = Ardread()
    
    if SoundPlay == 1:
        des = "/tmp/squid/effect/"

        sound.copy_file()
        doll_re = sound.play(des, "doll_sound")

        print(doll_re)
    else:
        print('false')