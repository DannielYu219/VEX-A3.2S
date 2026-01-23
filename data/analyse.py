import numpy as np
import matplotlib.pyplot as plt
import os
import argparse

SAMEPLE_TIME = 0.02
INPUT_FOLDER = 'data/text'  # 输入文件夹路径
OUTPUT_FOLDER = 'data/picture'  # 输出文件夹路径

def process_files(prefix):
    # 创建输出文件夹（如果不存在）
    os.makedirs(OUTPUT_FOLDER, exist_ok=True)

    # 遍历输入文件夹内的所有 .txt 文件
    for filename in os.listdir(INPUT_FOLDER):
        if filename.endswith('.txt') and filename.startswith(prefix):  # 仅处理符合前缀的 .txt 文件
            filepath = os.path.join(INPUT_FOLDER, filename)
            try:
                # 加载数据
                data = np.loadtxt(filepath, delimiter=',')
                input_data = data[:, 0]
                output_data = data[:, 1]
                size = data.shape[0]
                time = np.arange(0., SAMEPLE_TIME * size, SAMEPLE_TIME)
                
                # 绘制图像
                fig, ax = plt.subplots(2, 1, layout='constrained')
                ax[0].plot(time, input_data)
                ax[1].plot(time, output_data * 127 / 1000)
                ax[1].set_xlabel('time (sec)')
                ax[0].set_ylabel('position (mm)')
                ax[1].set_ylabel('voltage (V)')
                ax[0].set_xlim(0)
                ax[0].set_ylim(0)
                ax[1].set_xlim(0)
                ax[0].axhline(600, linewidth=0.5, color='r')
                ax[0].axhline(0, linewidth=0.5, color='r')
                ax[1].axhline(13, linewidth=0.5, color='r')
                ax[1].axhline(0, linewidth=0.5, color='r')
                
                # 保存图像
                output_filepath = os.path.join(OUTPUT_FOLDER, f"{os.path.splitext(filename)[0]}.jpg")
                fig.savefig(output_filepath)
                plt.close(fig)  # 关闭图像，释放内存
                print(f"Processed and saved: {output_filepath}")
            except Exception as e:
                print(f"Error processing {filename}: {e}")

if __name__ == '__main__':
    # 解析命令行参数
    parser = argparse.ArgumentParser(description="Process text files and generate images.")
    parser.add_argument('prefix', type=str, help="The prefix of text files to process.")
    args = parser.parse_args()

    # 处理指定前缀的文件
    process_files(args.prefix)