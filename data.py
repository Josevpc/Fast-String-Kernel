from Bio import SeqIO
import pandas as pd


def make_dataframe(n_samples):
    n_samples = int(n_samples/2)
    sequence_target = []

    for record in SeqIO.parse("dataset/ncRNA_datasets/hsa_ncRNA.fa", "fasta"):
        sequence_target.append(str(record.seq))
    
    data_target = {'Sequence' : sequence_target, 'target' : 1}
    df_target = pd.DataFrame(data=data_target)

    if len(df_target) >= n_samples:
        df_target = df_target.sample(n=n_samples)
    else:
        print('Numero de samples maior do que oque há no banco de dados')
        return 0

    sequence = []

    for record in SeqIO.parse("dataset/VERT_test_dataset/hsa_real.fa", "fasta"):
        sequence.append(str(record.seq))

    data = {'Sequence' : sequence, 'target' : 0}
    df = pd.DataFrame(data=data)
    if len(df) >= n_samples:
        df = df.sample(n=n_samples)
    else:
        print('Numero de samples maior do que oque há no banco de dados')
        return 0

    dataframe = pd.concat([df_target, df], ignore_index=True, sort=False)
    dataframe = dataframe.sample(frac=1).reset_index(drop=True)
    
    return dataframe

def make_csv(file_name, samples):
    make_dataframe(n_samples=samples).to_csv(file_name+'.csv', index=False)