from modules.sound import sound
import serial
import requests

# print('serial ' + serial.__version__)

# Set a PORT Number & baud rate
PORT = '/dev/cu.usbmodem142301'
# PORT = 'COM4'
BaudRate = 9600

ARD= serial.Serial(PORT,BaudRate)

def Decode(A):
    A = A.decode()
    A = str(A)

    if A[0]=='S':                       #첫문자 검사 SPEAK1
        if (len(A)==8):                #문자열 갯수 검사
            SoundPlay=int(A[5])
            result = SoundPlay
            return result + 9
        else : 
            print ("Error_lack of number _ %d" %len(A))
            return 0

    if A[0]=='F':
        if (len(A)==9):                #문자열 갯수 검사 FAILEP1
            outPlayer=int(A[6])
            result = outPlayer + 1
            return result
        else : 
            print ("Error_lack of number _ %d" %len(A))
            return 0
    else:
        return 0
        
def Ardread(): # return list [Ard1,Ard2]
    if ARD.readable():
        LINE = ARD.readline()
        code=Decode(LINE) 
        # print(code)
        return code
    else : 
        print("읽기 실패 from _Ardread_")


sound.copy_file()
response = requests.get('http://localhost/init')
response.status_code 
response.text

while (True):
    ReturnCode = Ardread()
    print(type(ReturnCode))
    des = "/tmp/squid/effect/"
    print(ReturnCode)
    if ReturnCode > 9:
        doll_re = sound.play(des, "doll_sound", ReturnCode-9)
    elif  ReturnCode == 2:
        print("1 번 탈락")
        sound.play(des, "gun_effect", 1)
        response = requests.get('http://localhost/player?player=p1&status=0')
        response.status_code 
        response.text
    elif  ReturnCode == 3:
        print("2 번 탈락")
        sound.play(des, "gun_effect", 1)
        response = requests.get('http://localhost/player?player=p2&status=0')
        response.status_code 
        response.text
    elif  ReturnCode == 4:
        print("3 번 탈락")
        sound.play(des, "gun_effect", 1)
        response = requests.get('http://localhost/player?player=p3&status=0')
        response.status_code 
        response.text
    elif  ReturnCode == 5:
        print("4 번 탈락")
        sound.play(des, "gun_effect", 1)
        response = requests.get('http://localhost/player?player=p4&status=0')
        response.status_code 
        response.text
    else:
        print('false')