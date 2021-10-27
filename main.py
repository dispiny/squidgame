from src.sound import sound
from random import * 
from src.web import api
from src.sound import move_effect
from multiprocessing import Pool
import os


def speak():
    rate = randint(2, 4)
    print('rate '+ str(rate) + 'x')
    sound.play_sound(rate)

def laser():
    sound.play_laser()

if __name__ == '__main__': 
    username = format(os.getlogin())
    
    move_effect.move(username)
    sound.play(username)