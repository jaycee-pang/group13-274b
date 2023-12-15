# import packages
import os
import glob
import argparse

import pandas as pd 
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation


def get_cell_states(input_file):
    # get all cell states from file and store in pandas dataframe
    if not glob.glob(input_file):
        raise FileNotFoundError(f"input file {input_file} does not exist")

    print("loading file...")
    cell_df = pd.read_csv(input_file, skiprows=7, sep=", ")
    end_time = max(cell_df["time_step"]) + 1
    return cell_df, end_time


def create_image(cell_df, time, name="Cellular_Automata"):
    # make plt image 
    sub_df = cell_df[cell_df["time_step"] == time]
    max_val = max(cell_df["value"])

    len_x = max(cell_df["x"]) + 1
    len_y = max(cell_df["y"]) + 1

    cell = np.zeros((len_x, len_y))

    for i in sub_df.index.values:
        x = sub_df.loc[i, "x"]
        y = sub_df.loc[i, "y"]
        value = sub_df.loc[i, "value"]

        cell[x][y] = value

    plt.imshow(cell, cmap="plasma", vmax=max_val)
    
    for (j, i), label in np.ndenumerate(cell):
        plt.text(i, j, int(label), ha='center', va='center')

    plt.title(f"{name} Cell States\n(t = {time})")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
                        prog='Visualize Cellular Automata Outputs',
                        description='Given cellular automata generated output .txt file, create images and gifs of automata simulation.')
    parser.add_argument("input_file", help="path to input automata .txt file")
    parser.add_argument("-o", "--output_dir", help="output directory to place .gif in")
    parser.add_argument("--automata_name", default="Cellular_Automata", help="name of automata (for saving file)")
    
    args = parser.parse_args()

    cell_df, n_frames = get_cell_states(args.input_file)

    def update(time):
        ax.clear()
        create_image(cell_df, time, args.automata_name)

    gif_path = os.path.join(args.output_dir, f"{args.automata_name}.gif")

    fig, ax = plt.subplots()

    gif = FuncAnimation(fig, update, frames=n_frames, interval=2000)

    gif.save(gif_path, writer="imagemagick")

    print(f"GIF saved to {gif_path}!")



