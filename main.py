from modules.sound import sound

des = "/tmp/squid/effect/"

sound.copy_file()
doll_re = sound.play(des, "doll_sound")

print(doll_re)