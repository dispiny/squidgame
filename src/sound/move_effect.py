
import shutil

def move(username):
    shutil.copyfile("./src/sound/effect/01.wav", "C:\\Users\\"+str(username)+"\\AppData\\Local\\Temp\\01.wav")
    shutil.copyfile("./src/sound/effect/02.wav", "C:\\Users\\"+str(username)+"\\AppData\\Local\\Temp\\02.wav")
    shutil.copyfile("./src/sound/effect/laser_ef.wav", "C:\\Users\\"+str(username)+"\\AppData\\Local\\Temp\\laser_ef.wav")