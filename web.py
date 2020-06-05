# -*- coding: utf-8 -*-

import dash
from dash.dependencies import Input, Output
import dash_auth
import dash_enterprise_auth as auth
import dash_core_components as dcc
import dash_html_components as html
import pandas as pd
import numpy as np

external_stylesheets = ['https://codepen.io/chriddyp/pen/bWLwgP.css']
app = dash.Dash(__name__, external_stylesheets=external_stylesheets)

VALID_USERNAME_PASSWORD_PAIRS = {
    'admin': 'admin'
}

auth = dash_auth.BasicAuth(
    app,
    VALID_USERNAME_PASSWORD_PAIRS
)

adress = 'C:\\Users\\Nikki_A\\Documents\\Programming\\python\\jakushkin\\logs.csv'
data = np.loadtxt(adress, delimiter=',', skiprows=1)
# file = pd.read_csv(adress, sep=',')
temp = data[:, 1]
gas = data[:, 0]
n = data.shape[0]
# print(n)
times = np.linspace(1, n, n)
# print(times)
co = gas[n-1]
C = temp[n-1]
out = ''

if((co <= 26.0) & (C > 26.0) & (C > 70)): out = "Now everything is okay"

if(((co > 70) & (C <= 30.0) & (C > 26.0)),
   ((co > 70) & (C <= 20.0) & (C > 18.0)),
   ((co > 70) & (C > 30.0)),
   ((co > 70) & (C <= 18))): out = "Now it's too hot"

if(((co > 40) & (co <= 70) & (co >= 30) & (C <= 26.0) & (C > 20.0)),
   ((co <= 40) & (C <= 26.0) & (C > 20.0))): out = "Now it's too stuffy"

app.layout = html.Div(children=[

    html.Div([
        html.H1('About your room:'),
        html.Div([
            html.P(out),
            html.P('Now your temperature is ' + str(temp[n-1]) + ', normal is more than 18 and less than 26'),
            html.P('Now your gas is ' + str(gas[n-1]) + ', normal is more than 70.'),
        ])
    ]),

    dcc.Graph(
        id='temperature',
        figure={
            'data': [
                {'x': times, 'y': temp},
            ],
            'layout': {
                'title': 'Temperature'
            }
        }
    ),

    dcc.Graph(
        id='Gas',
        figure={
            'data': [
                {'x': times, 'y': gas},
            ],
            'layout': {
                'title': 'Gas'
            }
        }
    )
])

if __name__ == '__main__':
    app.run_server(debug=True)
