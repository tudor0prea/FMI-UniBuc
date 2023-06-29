import pandas as pd
import numpy as np
import os
import csv
import re
from tensorflow import keras
from tensorflow.keras import layers
from tensorflow.keras.models import Sequential


def add_extension(x):
    x = x + ".png"
    return x


def generate_csv():
    dir_path = "C:\\works\\train\\data\\data"
    files = os.listdir(dir_path)
    png_files = [f for f in files if re.match(r'.*\.png', f)]

    with open('nume_fisiere.csv', mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(['id','class'])
        for f in png_files:
            writer.writerow([f,'0'])

 
def get_model(width=128, height=128, depth=64):

    inputs = keras.Input((width, height, depth, 1))

    x = layers.Conv3D(filters=64, kernel_size=3, activation="relu")(inputs)
    x = layers.MaxPool3D(pool_size=2)(x)
    x = layers.BatchNormalization()(x)

    x = layers.Conv3D(filters=64, kernel_size=3, activation="relu")(x)
    x = layers.MaxPool3D(pool_size=2)(x)
    x = layers.BatchNormalization()(x)

    x = layers.Conv3D(filters=128, kernel_size=3, activation="relu")(x)
    x = layers.MaxPool3D(pool_size=2)(x)
    x = layers.BatchNormalization()(x)

    x = layers.Conv3D(filters=256, kernel_size=3, activation="relu")(x)
    x = layers.MaxPool3D(pool_size=2)(x)
    x = layers.BatchNormalization()(x)

    x = layers.GlobalAveragePooling3D()(x)
    x = layers.Dense(units=512, activation="relu")(x)
    x = layers.Dropout(0.3)(x)

    outputs = layers.Dense(units=1, activation="sigmoid")(x)

    # Define the model.
    model = keras.Model(inputs, outputs, name="3dcnn")
    return model


#generate_csv();

# Citim fișierul CSV și încărcăm imaginile corespunzătoare
df = pd.read_csv('C:\\works\\train\\train_labels_short.txt',dtype=str)
df['id'] = df['id'].apply(add_extension)

#df = pd.read_csv('nume_fisiere.csv',dtype=str)

#df['id'] = df['id'].astype(str)

df['class'] = df['class'].astype(str)
# Definim un obiect ImageDataGenerator pentru a prelucra imaginile și a le încărca în model
datagen = keras.preprocessing.image.ImageDataGenerator(
    rescale=1./255
)

# Folosim flow_from_dataframe pentru a încărca datele din fișierul CSV
train_data = datagen.flow_from_dataframe(
    dataframe=df,
    directory='C:\\works\\train\\data\\data',
    x_col='id',
    y_col='class',
    target_size=(224, 224),
    batch_size=8,
    class_mode='binary'
)

print(train_data.class_indices)

# Definim arhitectura modelului CNN
model = Sequential([
    layers.Conv2D(16, (3,3), activation='relu', input_shape=(224, 224, 3)),
    layers.MaxPooling2D(pool_size=(2,2)),
    layers.Conv2D(32, (3,3), activation='relu'),
    layers.MaxPooling2D(pool_size=(2,2)),
    layers.Conv2D(64, (3,3), activation='relu'),
    layers.MaxPooling2D(pool_size=(2,2)),
    layers.Flatten(),
    layers.Dense(512, activation='relu'),
    layers.Dense(1, activation='sigmoid')
])

model13= get_model()

# Compilam modelul cu o functie de pierdere si un algoritm de optimizare
model.compile(
    loss='binary_crossentropy',
    optimizer='adam',
    metrics=['accuracy']
)

# Antrenam modelul pe datele de antrenament și validare
model.fit(
    train_data,
    epochs=5
)

# Salvam modelul antrenat
model.save('tomography_classification_model.h5')


