import winsound

def play(username):
    path = "C:\\Users\\"+username+"\\AppData\\Local\\Temp\\01.wav"

    winsound.PlaySound(path, winsound.SND_FILENAME)