import os
import shutil
import random

def copy_file():
    if os.path.isdir('/tmp/squid/effect'):
        os.system('rm -rf /tmp/squid')        
        os.system('mkdir -p ' + '/tmp/squid/effect')
        shutil.copy('/Users/sysop/Documents/project/squidgame/modules/sound/effect/doll_sound.mp3', '/tmp/squid/effect/doll_sound.mp3')
    else:
        os.system('mkdir -p ' + '/tmp/squid/effect')
        shutil.copy('/Users/sysop/Documents/project/squidgame/modules/sound/effect/doll_sound.mp3', '/tmp/squid/effect/doll_sound.mp3')

def play(music_location, music_track):
    rate = random.uniform(1.0, 5.0)

    print(f'play speed: {rate}')

    audio_file = music_location + music_track +".mp3"
    os.system('afplay -v 0.3 -r ' + str(rate) + ' ' + audio_file)
    return 1