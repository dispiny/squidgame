from modules.sound import sound
from modules.sound import control_files
import os 

if __name__ == '__main__':
    sound_track = ["doll_sound", "game_round", "main_theme", "original_sound"]
    src = "/Users/sysop/Documents/project/squidgame/modules/sound/effect/"
    des = "/tmp/squid/effects/"

    if os.path.isdir(des):
        print("isdir true")
        control_files.move_file(sound_track, src, des)
    else:
        print('isdir false')
        control_files.create_file(des)
        control_files.move_file(sound_track, src, des)
    
    sound.play(des, sound_track[2])