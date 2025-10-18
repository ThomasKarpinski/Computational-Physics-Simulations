import dash
import dash_bootstrap_components as dbc
from dash import dcc, Input, Output, html
import plotly.express as px
import pandas as pd
from callbacks import register_callbacks

def load_data():
    """
    Reads all CSV files without headers, giving them defined column names,
    and returns DataFrames in a single list.
    """
    all_df = []

    headers_txy = ["t", "x", "y"]
    headers_range_angle = ["angle", "range"]

    # Mapa wszystkich plików i nagłówków, które mają otrzymać
    file_map = {
        # Part 1: trajectory_no_drag (headers: t, x, y)
        "../trajectory_no_drag_10.csv": headers_txy,
        "../trajectory_no_drag_20.csv": headers_txy,
        "../trajectory_no_drag_50.csv": headers_txy,
        "../trajectory_no_drag_100.csv": headers_txy,
        "../trajectory_no_drag_200.csv": headers_txy,
        "../trajectory_no_drag_500.csv": headers_txy,

        # Part 2: trajectory_diff_drag_a0 (headers: t, x, y)
        "../task3_1/trajectory_diff_drag_a0_D0.000000.csv": headers_txy,
        "../task3_1/trajectory_diff_drag_a0_D0.000100.csv": headers_txy,
        "../task3_1/trajectory_diff_drag_a0_D0.000200.csv": headers_txy,
        "../task3_1/trajectory_diff_drag_a0_D0.000500.csv": headers_txy,
        "../task3_1/trajectory_diff_drag_a0_D0.001000.csv": headers_txy,

        # Part 3: range_vs_angle (headers: angle, range)
        "../task3_2/range_vs_angle_D0.000000.csv": headers_range_angle,
        "../task3_2/range_vs_angle_D0.001000.csv": headers_range_angle,
        "../task3_2/range_vs_angle_D0.002000.csv": headers_range_angle,

        # Part 4: trajectory_D0.001000 ((headers: t, x, y)
        "../task4/trajectory_D0.001000_a0.000000_alpha35.csv": headers_txy,
        "../task4/trajectory_D0.001000_a0.000000_alpha45.csv": headers_txy,
        "../task4/trajectory_D0.001000_a0.006500_alpha35.csv": headers_txy,
        "../task4/trajectory_D0.001000_a0.006500_alpha45.csv": headers_txy,
    }

    print("--- Rozpoczynam wczytywanie danych ---")

    for file_path, current_headers in file_map.items():
        try:
            df = pd.read_csv(file_path, header=None, names=current_headers)
            all_df.append(df)
        except FileNotFoundError:
            print(f"Ostrzeżenie: Nie znaleziono pliku {file_path}")
        except Exception as e:
            # Wyświetla błędy inne niż brak pliku (np. błędy parsowania)
            print(f"BŁĄD KRYTYCZNY przy wczytywaniu {file_path}: {e}")
            continue # Przejdź do następnego pliku

    print(f"\n--- Zakończono wczytywanie ---")
    print(f"Łącznie wczytano {len(all_df)} DataFrames.")

    return all_df

data = load_data()

# print(data)

app = dash.Dash(__name__, external_stylesheets=[dbc.themes.BOOTSTRAP])
app.layout = dbc.Container([
    dbc.Row([
        dbc.Col(html.H1("Projectile Trajectory Dashboard"), width=12, className="text-center my-5")
    ]),
    dbc.Row([
        dbc.Col(
            dbc.Card(
                dbc.CardBody([
                    html.Div([
                        html.H2("Trajectory without the drag force", className="card-title"),
                        dcc.Markdown('$D=0$, $v_{100}=0{[m/s]}, m=1{kg}, θ=45^{0}$', mathjax=True, className='my-class', id='my-p-element'),
                        dcc.RadioItems(
                            id='wybor-danych-radio',
                            options=[
                                {'label': ' n=10', 'value': '10'},
                                {'label': ' n=20', 'value': '20'},
                                {'label': ' n=50', 'value': '50'},
                                {'label': ' n=100', 'value': '100'},
                                {'label': ' n=200', 'value': '200'},
                                {'label': ' n=500', 'value': '500'}
                            ],
                            value='10',
                            inline=True,
                            labelStyle={'margin-right': '25px', 'margin-left': '10px'},
                            style={'margin-bottom': '20px'}
                        ),
                    
                    ], style={'text-align': 'center'}),
                ])
            ), width=12
        )]),
    dbc.Row([
        dbc.Col(
            dbc.Card(
                dbc.CardBody([
                    html.Div([
                        dcc.Graph(id="no-d")
                    ],)
                ])
            ), width=6
        ),
        dbc.Col(
            dbc.Card(
                dbc.CardBody([
                    html.Div([
                        # output component
                        html.Div(id='kontener-tabeli-radio')
                    ], style={'text-align': 'center'})
                ])
            ), width=6
        )
    ], className="text-center my-5"),

    dbc.Row([
        dbc.Col(
            dbc.Card(
                dbc.CardBody([
                    html.Div([
                        html.H2("Trajectory with various drag force"),
                        dcc.Slider(0, 10,
                            step=None,
                            marks={
                                0: '0',
                                3: '1 · 10^(-4)',
                                5: '2 · 10^(-4)',
                                7.65: '5 · 10^(-4)',
                                10: '10^(-3)'
                            },
                            value=0,
                            id="various-drag-slider"
                        )
                    ],),
                    dcc.Graph(id="various-drag"),
                    html.Div([
                    html.Div(id="container-various-drag")
                    ])
                ])
            ), width=12
        ),
        
    ], className="text-center my-5"),


    dbc.Row([
        dbc.Col(
            dbc.Card(
                dbc.CardBody([
                    html.H2("Maximum ranges for projectile scanning the firing angle θ for the various D"),
                    html.Div([
                    dcc.Dropdown(
                        options=[
                        {'label': '0', 'value': '0'},
                        {'label': '1 · 10^(-3)', 'value': '1'},
                        {'label': '2 · 10^(-3)', 'value': '2'},
                        ],value='0', id='close-on-select-dropdown', multi=True, closeOnSelect=False, placeholder="Select Drag Value")
                                        ],style={'textAlign': 'center'}),
                    dcc.Graph(id="angle-drag-figure")
                ], style={'textAlign': 'center'})
            ), width=12
        )
    ])
])

register_callbacks(app, data)


if __name__ == '__main__':
    app.run(debug=True)