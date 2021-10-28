import subprocess

def play(music_location, music_track):
    audio_file = music_location + music_track +".mp3"
    subprocess.call(["afplay", audio_file])