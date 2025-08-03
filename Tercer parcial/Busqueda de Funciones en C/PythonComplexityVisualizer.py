import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

def visualize_complexity(csv_path):
    # Leer el CSVx
    df = pd.read_csv(csv_path)
    
    # Crear mapa de complejidades a valores numéricos
    complexity_map = {
        'O(1)': 1,
        'O(n)': 2,
        'O(n^2)': 3,
        'O(n^3)': 4,
        'O(2^n)': 5
    }
    
    # Convertir complejidades a valores numéricos
    df['ComplexityValue'] = df['Complejidad'].map(complexity_map)
    
    # Crear visualizaciones
    plt.figure(figsize=(15, 10))
    
    # 1. Gráfico de barras de complejidad
    plt.subplot(2, 1, 1)
    sns.barplot(x='Nombre', y='ComplexityValue', data=df)
    plt.title('Complejidad por Función')
    plt.xticks(rotation=45)
    plt.ylabel('Nivel de Complejidad')
    
    # 2. Gráfico de pastel de distribución de complejidades
    plt.subplot(2, 1, 2)
    complexity_counts = df['Complejidad'].value_counts()
    plt.pie(complexity_counts, labels=complexity_counts.index, autopct='%1.1f%%')
    plt.title('Distribución de Complejidades')
    
    plt.tight_layout()
    plt.savefig('complexity_analysis.png')
    plt.show()
        # 3. Gráfico de barras apiladas para templates vs no-templates
    plt.subplot(3, 1, 3)
    template_complexity = pd.crosstab(df['Es Template'], df['Complejidad'])
    template_complexity.plot(kind='bar', stacked=True)
    plt.title('Complejidad por Tipo de Función')
    plt.xlabel('Es Template')
    plt.ylabel('Número de Funciones')
    
    plt.tight_layout()
    plt.savefig('complexity_analysis.png')
    plt.show()
    
    # Imprimir estadísticas adicionales
    print("\nEstadísticas de Complejidad:")
    print(df['Complejidad'].value_counts().to_string())
    print("\nFunciones Template vs No-Template:")
    print(df['Es Template'].value_counts().to_string())

if __name__ == "__main__":
    import sys
    if len(sys.argv) > 1:
        visualize_complexity(sys.argv[1])
    else:
        visualize_complexity('funciones_extraidas.csv')