from modules.sound import sound
import serial
# print('serial ' + serial.__version__)

# Set a PORT Number & baud rate
# PORT = '/dev/cu.usbmodem141301'
PORT = 'COM4'
BaudRate = 9600

ARD= serial.Serial(PORT,BaudRate)

def Decode(A):
    A = A.decode()
    A = str(A)

    if A[0]=='S':                       #첫문자 검사 SPEAK1
        if (len(A)==8):                #문자열 갯수 검사
            SoundPlay=int(A[5])
            result = SoundPlay
            return result
        else : 
            print ("Error_lack of number _ %d" %len(A))
            return False

    if A[0]=='F':
        if (len(A)==9):                #문자열 갯수 검사 FAILEP1
            outPlayer=int(A[6])
            result = outPlayer + 1
            return result
        else : 
            print ("Error_lack of number _ %d" %len(A))
            return False
    
def Ardread(): # return list [Ard1,Ard2]
        if ARD.readable():
            LINE = ARD.readline()
            code=Decode(LINE) 
            # print(code)
            return code
        else : 
            print("읽기 실패 from _Ardread_")


while (True):
    ReturnCode = Ardread()
    
    if ReturnCode == 1:
        des = "/tmp/squid/effect/"

        sound.copy_file()
        doll_re = sound.play(des, "doll_sound")

        print(doll_re)
    elif  ReturnCode == 2:
        print("1 번 탈락")
    elif  ReturnCode == 3:
        print("2 번 탈락")
    elif  ReturnCode == 4:
        print("3 번 탈락")
    elif  ReturnCode == 5:
        print("4 번 탈락")
    else:
        print('false')