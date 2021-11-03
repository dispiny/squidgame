from flask_restful import Api, Resource, reqparse
from flask import Flask, render_template, send_from_directory
from modules.sound import sound
import os
import logging

logging.basicConfig(filename = "logs/project.log", level=logging.DEBUG)

app = Flask('My First App')
api = Api(app)

@app.route('/')
def index():
    return render_template('index.html')
    
class PlayerStatus(Resource):
    def get(self):
        try:
            parser = reqparse.RequestParser()
            parser.add_argument('player', required=True, type=int, help='player cannot be blank')
            parser.add_argument('status', required=True, type=int, help='statuc cannot be blank')
            args = parser.parse_args()
            result = args['player']
            if args['status'] == 1: # 0 생존, 1 탈락
                return {'result': str(result) + '번 탈락'}
            else:
                return {'result': str(result) + '번 생존'}
        except Exception as e:
            return {'error': str(e)}

api.add_resource(PlayerStatus, '/player')

if __name__ == '__main__':
    app.run(host='0.0.0.0', port='80', debug=True)
