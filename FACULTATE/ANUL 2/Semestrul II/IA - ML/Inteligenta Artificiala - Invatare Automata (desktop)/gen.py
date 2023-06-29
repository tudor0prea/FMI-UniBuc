import pandas as pd
import numpy as np
import os
import csv
import re
from tensorflow import keras
from tensorflow.keras import layers
from tensorflow.keras.models import Sequential


input_csv_name = 'C:\\works\\train\\sample_submission.txt'
dir_path = "C:\\works\\train\\data\\data"
model_path = 'tomography_classification_model.h5'
output_csv = 'sample_submission_2022_05_04.txt'

def add_extension(x):
    x = x + ".png"
    return x


def get_class(predictions):
    class_labels = ['1', '0']
    predicted_class_indices = np.argmax(predictions, axis=1)
    return [class_labels[predicted_class_indices[i]] for i in range(len(predicted_class_indices))]

 

# Citim fișierul CSV și încărcăm imaginile corespunzătoare

df = pd.read_csv(input_csv_name,dtype=str)
df['id'] = df['id'].apply(add_extension)


# Definim un obiect ImageDataGenerator pentru a prelucra imaginile și a le încărca în model
datagen = keras.preprocessing.image.ImageDataGenerator(
    rescale=1./255
)

# Folosim flow_from_dataframe pentru a încărca datele din fișierul CSV
test_generator = datagen.flow_from_dataframe(
    dataframe=df,
    directory=dir_path,
    x_col='id',
    target_size=(224, 224),
    batch_size=1,
    shuffle=False,
    class_mode=None
)
# Incarcam modelul antrenat
model = keras.models.load_model(model_path)

# Generam predicțiile modelului pe datele noi
predictions = model.predict(test_generator)

lst = [] 
for i in range(len(predictions)):
        if predictions[i][0]<0.5:
             lst.append(0)
        else:
             lst.append(1)
              





# Salvam predicțiile într-un fișier CSV
df_predictions = pd.DataFrame({'id': df['id'], 'class': lst})
df_predictions.to_csv(output_csv, index=False)



