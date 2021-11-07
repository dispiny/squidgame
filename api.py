from flask_restful import Api, Resource, reqparse
from flask import Flask, render_template, send_from_directory
from modules.sound import sound
import os
import logging
import redis


logging.basicConfig(filename = "logs/project.log", level=logging.DEBUG)

app = Flask('My First App')
api = Api(app)

rd = redis.StrictRedis(host='localhost', port=6379, db=0, password='Skill39')


def init_set_status():
    rd.set("p1", "2")
    rd.set("p2", "2")
    rd.set("p3", "2")
    rd.set("p4", "2")

def set_status(player, status):
    if player == 'p1':
        rd.set("p1", status)
    elif player == 'p2':
        rd.set("p2", status)
    elif player == 'p3':
        rd.set("p3", status)
    elif player == 'p4':
        rd.set("p4", status)
    
def get_status():
    p1 = rd.get("p1")
    p2 = rd.get("p2")
    p3 = rd.get("p3")
    p4 = rd.get("p4")

    p_list = [str(p1.decode('ascii')), str(p2.decode('ascii')), str(p3.decode('ascii')), str(p4.decode('ascii'))]

    return p_list

@app.route('/')
def index():
    return render_template('index.html')
    
@app.route('/init')
def init():
    init_set_status()
    return 'Finished'

@app.route('/score')
def score():
    status = get_status()

    if status[0] == '1':
        p1_st = '성공'
    elif status[0] == '2':
        p1_st = '경기 중'
    elif status[0] == '0':
        p1_st = '탈락'

    if status[1] == '1':
        p2_st = '성공'
    elif status[1] == '2':
        p2_st = '경기 중'
    elif status[1] == '0':
        p2_st = '탈락'

    if status[2] == '1':
        p3_st = '성공'
    elif status[2] == '2':
        p3_st = '경기 중'
    elif status[2] == '0':
        p3_st = '탈락'

    if status[3] == '1':
        p4_st = '성공'
    elif status[3] == '2':
        p4_st = '경기 중'
    elif status[3] == '0':
        p4_st = '탈락'

    return render_template('score.html', p1=p1_st, p2=p2_st, p3=p3_st, p4=p4_st)
    # , p1=status[0], p2=status[1], p3=status[2], p4=status[4]


class PlayerStatus(Resource):
    def get(self):
        try:
            parser = reqparse.RequestParser()
            parser.add_argument('player', required=True, type=str, help='player cannot be blank')
            parser.add_argument('status', required=True, type=str, help='statuc cannot be blank')
            args = parser.parse_args()
            player = args['player']
            status = args['status']

            if status == '0': # 1 생존, 0 탈락
                set_status(player, status)
                get_status()
                return {'number': str(player), 'status': 'Failed'}
            elif status == '1':
                set_status(player, status)
                get_status()
                return {'number': str(player), 'status': 'Save'}
            elif status == '2':
                set_status(player, status)
                get_status()
                return {'number': str(player), 'status': 'playing'}
        except Exception as e:
            return {'error': str(e)}

api.add_resource(PlayerStatus, '/player')

    
if __name__ == '__main__':
    app.run(host='0.0.0.0', port='80', debug=True)
