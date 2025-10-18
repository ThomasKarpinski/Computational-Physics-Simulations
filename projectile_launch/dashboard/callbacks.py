import dash
import dash_bootstrap_components as dbc
from dash import dcc, Input, Output, html
import plotly.express as px
import plotly.graph_objects as go
import pandas as pd

def register_callbacks(app, data):
    @app.callback(
    Output('no-d', 'figure'),
    Input('wybor-danych-radio', 'value')
    )
    def update_graph_no_d(n_chosen):
        values = [10, 20, 50, 100, 200, 500]
        df = None
        for value in range(len(values)+1):
            if n_chosen == str(values[value]):
                df = data[value]
                break
        if df is None:
            return {}
        fig = px.line(df, x="x", y="y")

        max_y_row = df.loc[df['y'].idxmax()] 

        max_x = max_y_row['x']
        max_y = max_y_row['y']
        
        
        fig.add_annotation(
            x=max_x,
            y=max_y,
            text=f"Y MAX: {max_y:.2f}", 
            
            # stylization
            showarrow=True,
            arrowhead=1,
            arrowsize=1,
            arrowwidth=1,
            yshift=15, # Label shift above point
            font=dict(
                family="Arial, sans-serif",
                size=14,
                color="#CC0000" # Label color
            ),
            bgcolor="rgba(255, 255, 255, 0.7)",
            bordercolor="#CC0000",
            borderwidth=1,
            borderpad=4
        )

        fig.update_layout(
        xaxis=dict(
            range=[0, 1200], 
            autorange=False 
        ),
        yaxis=dict(
            range=[0, 350], 
            autorange=False 
        ))
            
        return fig

    @app.callback(
        # OUTPUT: Update 'children' of the container
        Output('kontener-tabeli-radio', 'children'),
        # INPUT: Get the 'value' attribute from RadioItems
        [Input('wybor-danych-radio', 'value')]
    )
    def aktualizuj_tabele_radio(selected_value):
        values = [10, 20, 50, 100, 200, 500]
        df = None 
        title = None
        for value in range(len(values)+1):
            if selected_value == str(values[value]):
                df = data[value]
                title = f"Trajectory data for n={values[value]}"
                break
        if df is None:
            return html.P("Table not selected")
        
        tabela = dbc.Table.from_dataframe(
            df, 
            striped=True, 
            bordered=True,
            hover=True,
        )
            
        # We return the finished table dbc.Table.from_dataframe
        return html.Div([
            html.H4(title),
            html.Div(
                children=[tabela],
                style={
                    'height': '400px',        
                    'overflowY': 'scroll',    
                    'overflowX': 'auto',
                    'border': '1px solid #ccc',
                }
            )
        ])


    @app.callback(
        Output('various-drag', 'figure'),
        Input('various-drag-slider', 'value')
    )
    def update_various_drag(d_value):
        values = [0, 3, 5, 7.65, 10]
        df = None
        for value in range(len(values) + 1):
            if d_value == values[value]:
                df = data[value + 6]
                break
        fig = px.line(df, x="x", y="y")

        fig.update_layout(
        xaxis=dict(
            range=[0, 1200], 
            autorange=False 
        ),
        yaxis=dict(
            range=[0, 300], 
            autorange=False 
        ))

        max_y_row = df.loc[df['y'].idxmax()] 

        max_x = max_y_row['x']
        max_y = max_y_row['y']
        
        
        
        fig.add_annotation(
            x=max_x,
            y=max_y,
            text=f"Y MAX: {max_y:.2f}", 
            
            showarrow=True,
            arrowhead=1,
            arrowsize=1,
            arrowwidth=1,
            yshift=15,
            font=dict(
                family="Arial, sans-serif",
                size=14,
                color="#CC0000"
            ),
            bgcolor="rgba(255, 255, 255, 0.7)",
            bordercolor="#CC0000",
            borderwidth=1,
            borderpad=4
        )
        max_x_row = df.loc[df['x'].idxmax()] 

        max_x_2 = max_x_row['x']
        max_y_2 = max_x_row['y']
        
        
        
        fig.add_annotation(
            x=max_x_2,
            y=max_y_2,
            text=f"X MAX: {max_x_2:.2f}", 
            
            showarrow=True,
            arrowhead=1,
            arrowsize=1,
            arrowwidth=1,
            yshift=0,
            xshift=0,
            font=dict(
                family="Arial, sans-serif",
                size=14,
                color="#3ACC00"
            ),
            bgcolor="rgba(255, 255, 255, 0.7)",
            bordercolor="#3ACC00",
            borderwidth=1,
            borderpad=4
        )

        return fig


    @app.callback(
        Output('container-various-drag', 'children'),
        Input('various-drag-slider', 'value')
    )
    def update_Various_drag_data(selected_value):
        values = [0, 3, 5, 7.65, 10]
        df = None 
        title = None
        for value in range(len(values)+1):
            if selected_value == values[value]:
                df = data[value+6]
                title = f"Trajectory data"
                break
        if df is None:
            return html.P("Table not selected")
        
        tabela = dbc.Table.from_dataframe(
            df, 
            striped=True, 
            bordered=True,
            hover=True,
        )
            
        return html.Div([
            html.H4(title),
            html.Div(
                children=[tabela],
                style={
                    'height': '200px',
                    'overflowY': 'scroll',
                    'overflowX': 'auto',
                    'border': '1px solid #ccc',
                }
            )
        ])
    
    @app.callback(
        Output('angle-drag-figure', 'figure'),
        Input('close-on-select-dropdown', 'value')
    )
    def update_angle(selected_D_values):

        data_by_D = {
            "0": data[11],
            "1": data[12],
            "2": data[13],
        }
        fig = go.Figure()

        # we add lines for selected D
        for D in selected_D_values:
            df = data_by_D.get(D)
            if df is None:
                continue
            if df is not None:
                label = f"D = {float(D)*1e-3:.1e}"
                fig.add_trace(go.Scatter(
                    x=df["angle"],
                    y=df["range"],
                    mode="lines",
                    name=label
                ))

        fig.update_layout(
            title="Range vs Firing Angle θ",
            xaxis_title="Angle θ (degrees)",
            yaxis_title="Range (m)",
            template="plotly_white"
        )

        return fig