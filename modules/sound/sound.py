import os
import shutil
import random

def copy_file():
    if os.path.isdir('/tmp/squid/effect'):
        os.system('rm -rf /tmp/squid')        
        os.system('mkdir -p ' + '/tmp/squid/effect')
        shutil.copy('/Users/sysop/Documents/project/squidgame/modules/sound/effect/doll_sound.mp3', '/tmp/squid/effect/doll_sound.mp3')
        shutil.copy('/Users/sysop/Documents/project/squidgame/modules/sound/effect/gun_effect.mp3', '/tmp/squid/effect/gun_effect.mp3')
        shutil.copy('/Users/sysop/Documents/project/squidgame/modules/sound/effect/1_suc.mp3', '/tmp/squid/effect/1_suc.mp3')
        shutil.copy('/Users/sysop/Documents/project/squidgame/modules/sound/effect/2_suc.mp3', '/tmp/squid/effect/2_suc.mp3')
        shutil.copy('/Users/sysop/Documents/project/squidgame/modules/sound/effect/1_fai.mp3', '/tmp/squid/effect/1_fai.mp3')
        shutil.copy('/Users/sysop/Documents/project/squidgame/modules/sound/effect/2_fai.mp3', '/tmp/squid/effect/2_fai.mp3')
    else:
        os.system('mkdir -p ' + '/tmp/squid/effect')
        shutil.copy('/Users/sysop/Documents/project/squidgame/modules/sound/effect/doll_sound.mp3', '/tmp/squid/effect/doll_sound.mp3')
        shutil.copy('/Users/sysop/Documents/project/squidgame/modules/sound/effect/gun_effect.mp3', '/tmp/squid/effect/gun_effect.mp3')
        shutil.copy('/Users/sysop/Documents/project/squidgame/modules/sound/effect/1_suc.mp3', '/tmp/squid/effect/1_suc.mp3')
        shutil.copy('/Users/sysop/Documents/project/squidgame/modules/sound/effect/2_suc.mp3', '/tmp/squid/effect/2_suc.mp3')
        shutil.copy('/Users/sysop/Documents/project/squidgame/modules/sound/effect/1_fai.mp3', '/tmp/squid/effect/1_fai.mp3')
        shutil.copy('/Users/sysop/Documents/project/squidgame/modules/sound/effect/2_fai.mp3', '/tmp/squid/effect/2_fai.mp3')

def play(music_location, music_track, rate):
    print(f'play speed: {rate}')

    audio_file = music_location + music_track +".mp3"
    os.system('afplay -v 0.3 -r ' + str(rate) + ' ' + audio_file)