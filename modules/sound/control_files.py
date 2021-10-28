import shutil
import os

def create_file(des):
    try:
        os.makedirs(des)
    except OSError:
        print("Creation of the directory %s failed" % des)
    else:
        print("Successfully created the directory %s" % des)

def move_file(sound_track, src, des):
    for i in range(len(sound_track)):
        music_scr = src + str(sound_track[i]) + ".mp3"
        music_des = des + str(sound_track[i]) + ".mp3"
        shutil.copy(music_scr, music_des)
