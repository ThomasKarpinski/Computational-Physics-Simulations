import dash
import dash_bootstrap_components as dbc
from dash import dcc, Input, Output, html
import plotly.express as px
import plotly.graph_objects as go
import pandas as pd

DROPDOWN_MAPPING = {
    '0': {'label': 'D=0', 'value_in_data': 11},
    '1': {'label': 'D=0.001', 'value_in_data': 12},
    '2': {'label': 'D=0.002', 'value_in_data': 13},
}

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
    
    @app.callback(
        Output('container-angle-drag', 'children'),
        Input('close-on-select-dropdown', 'value')
    )
    def update_angle_drag_data(selected_value):
        data_by_D = {
            "0": data[11].copy(),  # D=0.000000 (range_vs_angle)
            "1": data[12].copy(),  # D=0.001000 (range_vs_angle)
            "2": data[13].copy(),  # D=0.002000 (range_vs_angle)
        }

        if not selected_value:
            return html.P("Select the resistance coefficients (D) to display the data in the table.", className="text-muted")

        first_key = selected_value[0]
        result_df = data_by_D.get(first_key)
        first_label = DROPDOWN_MAPPING.get(first_key)['label']
        
        result_df.rename(columns={'range': f"Range ({first_label})"}, inplace=True)

        for D_key in selected_value[1:]:
            df_to_merge = data_by_D.get(D_key)
            
            new_col_name = f"Range ({DROPDOWN_MAPPING.get(D_key)['label']})"
            df_to_merge.rename(columns={'range': new_col_name}, inplace=True)
            
            result_df = pd.merge(
                result_df, 
                df_to_merge, 
                on='angle', # Key for linking: first column
                how='outer'  # Using “outer” to keep all rows from both DFs
            )
        
        df_display = result_df.head(51)
        
        tabela = dbc.Table.from_dataframe(
            df_display, 
            striped=True, 
            bordered=True,
            hover=True,
            size='sm'
        )
            
        return html.Div([
            html.P(f"The first {len(df_display)} lines after the connection were displayed.", className="text-muted small"),
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
        Output('altitude-graph','figure'),
        Input('switch-button', 'n_clicks')
        )
    def display_altitude_graph(n_clicks):
        df = None

        df_al35_a0 = data[14]
        df_al45_a0 = data[15]
        df_al35_a = data[16]
        df_al45_a = data[17]

        if df_al35_a0.empty:
            return go.Figure().update_layout(title="No data to display (CSV files have not been loaded).")
        
        clicks_count = n_clicks if n_clicks is not None else 0

        if clicks_count % 2 != 0:
            fig = go.Figure()
            fig.add_trace(go.Scatter(x=df_al35_a0['x'], y=df_al35_a0['y'], name='alpha=35, a=0',
                            line=dict(color='royalblue', width=4)))
            fig.add_trace(go.Scatter(x=df_al45_a0['x'], y=df_al45_a0['y'], name='alpha=45, a=0',
                            line=dict(color='firebrick', width=4)))
            fig.add_trace(go.Scatter(x=df_al35_a['x'], y=df_al35_a['y'], name='alpha=35, a>0',
                            line=dict(color='royalblue', width=4, dash='dash')))
            fig.add_trace(go.Scatter(x=df_al45_a['x'], y=df_al45_a['y'], name='alpha=45, a>0',
                            line=dict(color='firebrick', width=4, dash='dash')))
            
        else:
            fig = go.Figure()
            fig.add_trace(go.Scatter(x=df_al35_a0['x'], y=df_al35_a0['y'], name='alpha=35, a=0',
                            line=dict(color='royalblue', width=4)))
            fig.add_trace(go.Scatter(x=df_al45_a0['x'], y=df_al45_a0['y'], name='alpha=45, a=0',
                            line=dict(color='firebrick', width=4)))
            
        fig.update_layout(
                xaxis=dict(
                    title=dict(
                        text='x(m)'
                    )
                ),
                yaxis=dict(
                    title=dict(
                        text='y(m)'
                    )
                ),
        )
        
        return fig