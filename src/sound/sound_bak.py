import vlc

class VlcPlayer:    
    def __init__(self, *args):
        if args:
            instance = vlc.Instance(*args)
            self.media = instance.media_player_new()
        else:
            self.media = vlc.MediaPlayer()
 
    def video_set_scale(self, size):
        self.media.video_set_scale(size)

    def video_set_position(self, position):
        self.media.set_position(position)

    def set_uri(self, mrl):
        self.media.set_mrl(mrl)
 
    def play(self, path=None):
        if path:
            self.set_uri(path)
            return self.media.play()
        else:
            return self.media.play()
 
    def get_rate(self):
        return self.media.get_rate()
 
    def set_rate(self, rate):
        return self.media.set_rate(rate)
 
    def set_ratio(self, ratio):
        '''
        Set the aspect ratio (such as "16:9", "4:3")
        :param ratio:
        :return:
        '''
        # Must be set to 0, otherwise the screen width and height cannot be modified
        self.media.video_set_scale(0) 
        self.media.video_set_aspect_ratio(ratio)

    def add_callback(self, event_type, callback):
        self.media.event_manager().event_attach(event_type, callback)
 
    def remove_callback(self, event_type, callback):
        self.media.event_manager().event_detach(event_type, callback)

def my_call_back(event):
    print("Callback: exit")
    global status 
    status = 1 

def laser_call_back(event):
    print("Callback: exit")
    global laser_status 
    laser_status = 1 

status = 0

def play_sound(rate):
    print('Ready Now ... ')
    media_file = "src/sound/effect/speak_ef.mp4"
    player = VlcPlayer()
    player.video_set_scale(0.001)
    player.video_set_position(0.01)
    player.add_callback(vlc.EventType.MediaPlayerStopped, my_call_back)
    player.play(media_file)
    player.set_rate(rate)
    while True:
        if status == 1:
            break
        else:
            pass

laser_status = 0

def play_laser():
    print('Detection Now ... ')
    media_file = "src/sound/effect/laser_ef.mp4"
    player = VlcPlayer()
    player.video_set_scale(0.001)
    player.video_set_position(0.01)
    player.add_callback(vlc.EventType.MediaPlayerStopped, laser_call_back)
    player.play(media_file)
    while True:
        if laser_status == 1:
            break
        else:
            pass


