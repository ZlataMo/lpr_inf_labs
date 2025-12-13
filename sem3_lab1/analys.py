import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
import os
from matplotlib import rcParams

# Настройки стиля
plt.style.use('seaborn-v0_8-whitegrid')
rcParams['font.family'] = 'DejaVu Sans'
rcParams['figure.figsize'] = (14, 10)
rcParams['axes.titlesize'] = 16
rcParams['axes.labelsize'] = 14

def create_combined_plot(d100_files, d6_files, theoretical_file=None):
    """
    Создаёт комбинированные гистограммы для всех распределений
    """
    fig, axes = plt.subplots(2, 3, figsize=(18, 12))
    axes = axes.flatten()
    
    # Цвета для разных распределений
    colors = {
        'normal': '#3498db',
        'penalty': '#e74c3c', 
        'bonus': '#2ecc71',
        'theory': '#9b59b6'
    }
    
    # === График 1: D100 нормальный ===
    if os.path.exists(d100_files['normal']):
        df = pd.read_csv(d100_files['normal'])
        ax = axes[0]
        ax.bar(df['value'], df['probability'], color=colors['normal'], alpha=0.7)
        ax.set_title('D100: Нормальный бросок')
        ax.set_xlabel('Значение')
        ax.set_ylabel('Вероятность')
        ax.set_xlim(0, 31)
        ax.grid(True, alpha=0.3)
    
    # === График 2: D100 penalty ===
    if os.path.exists(d100_files['penalty']):
        df = pd.read_csv(d100_files['penalty'])
        ax = axes[1]
        ax.bar(df['value'], df['probability'], color=colors['penalty'], alpha=0.7)
        ax.set_title('D100: Штраф (минимум из двух)')
        ax.set_xlabel('Значение')
        ax.set_ylabel('Вероятность')
        ax.set_xlim(0, 31)
        ax.grid(True, alpha=0.3)
    
    # === График 3: D100 bonus ===
    if os.path.exists(d100_files['bonus']):
        df = pd.read_csv(d100_files['bonus'])
        ax = axes[2]
        ax.bar(df['value'], df['probability'], color=colors['bonus'], alpha=0.7)
        ax.set_title('D100: Преимущество (максимум из двух)')
        ax.set_xlabel('Значение')
        ax.set_ylabel('Вероятность')
        ax.set_xlim(0, 31)
        ax.grid(True, alpha=0.3)
    
    # === График 4: 3D6 нормальный (эксперимент vs теория) ===
    if os.path.exists(d6_files['normal']) and os.path.exists(theoretical_file):
        df_exp = pd.read_csv(d6_files['normal'])
        df_theory = pd.read_csv(theoretical_file)
        
        ax = axes[3]
        width = 0.35
        x = np.arange(len(df_exp))
        
        ax.bar(x - width/2, df_exp['probability'], width, 
               color=colors['normal'], alpha=0.7, label='Эксперимент')
        ax.bar(x + width/2, df_theory['probability'], width, 
               color=colors['theory'], alpha=0.7, label='Теория')
        
        ax.set_title('3D6: Нормальный бросок\n(Эксперимент vs Теория)')
        ax.set_xlabel('Сумма кубиков')
        ax.set_ylabel('Вероятность')
        ax.set_xticks(x)
        ax.set_xticklabels(df_exp['value'])
        ax.legend()
        ax.grid(True, alpha=0.3)
    
    # === График 5: 3D6 penalty ===
    if os.path.exists(d6_files['penalty']):
        df = pd.read_csv(d6_files['penalty'])
        ax = axes[4]
        ax.bar(df['value'], df['probability'], color=colors['penalty'], alpha=0.7)
        ax.set_title('3D6: Штраф (минимум из двух бросков)')
        ax.set_xlabel('Сумма кубиков')
        ax.set_ylabel('Вероятность')
        ax.grid(True, alpha=0.3)
    
    # === График 6: 3D6 bonus ===
    if os.path.exists(d6_files['bonus']):
        df = pd.read_csv(d6_files['bonus'])
        ax = axes[5]
        ax.bar(df['value'], df['probability'], color=colors['bonus'], alpha=0.7)
        ax.set_title('3D6: Преимущество (максимум из двух бросков)')
        ax.set_xlabel('Сумма кубиков')
        ax.set_ylabel('Вероятность')
        ax.grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.savefig('all_histograms.png', dpi=300, bbox_inches='tight')
    plt.show()
    
    print("✅ Все гистограммы сохранены в 'all_histograms.png'")

def create_comparison_plot(d100_files, d6_files):
    """
    Создаёт графики сравнения нормальный/penalty/bonus для D100 и 3D6
    """
    fig, axes = plt.subplots(1, 2, figsize=(16, 6))
    
    colors = ['#3498db', '#e74c3c', '#2ecc71']
    labels = ['Нормальный', 'Штраф', 'Преимущество']
    
    # === D100 сравнение ===
    ax1 = axes[0]
    
    for i, (key, color) in enumerate(zip(['normal', 'penalty', 'bonus'], colors)):
        filepath = d100_files.get(key)
        if filepath and os.path.exists(filepath):
            df = pd.read_csv(filepath)
            ax1.plot(df['value'], df['probability'], 
                    color=color, linewidth=2, marker='o', 
                    markersize=4, label=labels[i])
    
    ax1.set_title('D100: Сравнение распределений', fontsize=16)
    ax1.set_xlabel('Значение', fontsize=14)
    ax1.set_ylabel('Вероятность', fontsize=14)
    ax1.legend(fontsize=12)
    ax1.grid(True, alpha=0.3)
    ax1.set_xlim(0, 31)
    
    # === 3D6 сравнение ===
    ax2 = axes[1]
    
    for i, (key, color) in enumerate(zip(['normal', 'penalty', 'bonus'], colors)):
        filepath = d6_files.get(key)
        if filepath and os.path.exists(filepath):
            df = pd.read_csv(filepath)
            ax2.plot(df['value'], df['probability'], 
                    color=color, linewidth=2, marker='s', 
                    markersize=5, label=labels[i])
    
    ax2.set_title('3D6: Сравнение распределений', fontsize=16)
    ax2.set_xlabel('Сумма кубиков', fontsize=14)
    ax2.set_ylabel('Вероятность', fontsize=14)
    ax2.legend(fontsize=12)
    ax2.grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.savefig('comparison_plots.png', dpi=300, bbox_inches='tight')
    plt.show()
    
    print("✅ Графики сравнения сохранены в 'comparison_plots.png'")

def calculate_and_print_statistics():
    """
    Вычисляет и выводит статистики из данных
    """
    print("\n" + "="*60)
    print("СТАТИСТИЧЕСКИЕ ХАРАКТЕРИСТИКИ")
    print("="*60)
    
    files_to_check = [
        ('d100_normal.csv', 'D100 Нормальный'),
        ('d100_penalty.csv', 'D100 Штраф'),
        ('d100_bonus.csv', 'D100 Преимущество'),
        ('3d6_normal.csv', '3D6 Нормальный'),
        ('3d6_penalty.csv', '3D6 Штраф'),
        ('3d6_bonus.csv', '3D6 Преимущество')
    ]
    
    for filename, label in files_to_check:
        if os.path.exists(filename):
            df = pd.read_csv(filename)
            
            # Матожидание
            expectation = np.sum(df['value'] * df['probability'])
            
            # Дисперсия
            variance = np.sum((df['value'] - expectation) ** 2 * df['probability'])
            
            # Наиболее вероятное значение
            most_probable = df.loc[df['probability'].idxmax(), 'value']
            
            print(f"\n{label}:")
            print(f"  Матожидание: {expectation:.4f}")
            print(f"  Дисперсия: {variance:.4f}")
            print(f"  СКО: {np.sqrt(variance):.4f}")
            print(f"  Наиболее вероятное значение: {most_probable}")
            
            # Для D100 дополнительно
            if 'D100' in label:
                prob_gt_90 = df[df['value'] > 90]['probability'].sum()
                prob_lt_10 = df[df['value'] < 10]['probability'].sum()
                print(f"  P(>90): {prob_gt_90:.4f}")
                print(f"  P(<10): {prob_lt_10:.4f}")

def main():
    """
    Основная функция для построения всех графиков
    """
    print("="*60)
    print("ПОСТРОЕНИЕ ГИСТОГРАММ ДЛЯ ЗАДАНИЯ 2")
    print("="*60)
    
    # Файлы с данными
    d100_files = {
        'normal': 'd100_normal.csv',
        'penalty': 'd100_penalty.csv',
        'bonus': 'd100_bonus.csv'
    }
    
    d6_files = {
        'normal': '3d6_normal.csv',
        'penalty': '3d6_penalty.csv',
        'bonus': '3d6_bonus.csv'
    }
    
    theoretical_file = '3d6_theoretical.csv'
    
    # Проверка наличия файлов
    print("\n🔍 Проверка файлов с данными...")
    all_files = list(d100_files.values()) + list(d6_files.values()) + [theoretical_file]
    missing_files = [f for f in all_files if not os.path.exists(f)]
    
    if missing_files:
        print(f"❌ Отсутствуют файлы: {missing_files}")
        print("Сначала запустите C++ программу для генерации данных.")
        return
    
    print("✅ Все файлы данных найдены!")
    
    # 1. Создаём комбинированные гистограммы
    print("\n📊 Создаю комбинированные гистограммы...")
    create_combined_plot(d100_files, d6_files, theoretical_file)
    
    # 2. Создаём графики сравнения
    print("\n📈 Создаю графики сравнения...")
    create_comparison_plot(d100_files, d6_files)
    
    # 3. Вычисляем статистики
    print("\n🧮 Вычисляю статистические характеристики...")
    calculate_and_print_statistics()
    
    # 4. Дополнительный график: как меняется матожидание
    print("\n📉 Создаю график изменения матожидания...")
    create_expectation_chart()
    
    print("\n" + "="*60)
    print("✅ ВСЕ ГРАФИКИ ПОСТРОЕНЫ!")
    print("="*60)
    print("\nСозданные файлы:")
    print("  - all_histograms.png: все гистограммы на одном полотне")
    print("  - comparison_plots.png: сравнение распределений")
    print("  - expectation_chart.png: изменение матожидания")
    print("\nДанные для анализа сохранены в CSV файлах.")

def create_expectation_chart():
    """
    Дополнительный график: как штраф/бонус влияют на матожидание
    """
    fig, ax = plt.subplots(figsize=(10, 6))
    
    # Теоретические значения для разных max
    max_values = list(range(2, 21)) + [50, 100]
    normal_expectations = []
    penalty_expectations = []
    bonus_expectations = []
    
    for max_val in max_values:
        # Теория
        normal = (1 + max_val) / 2
        
        # Penalty (минимум двух)
        penalty_sum = 0
        for k in range(1, max_val + 1):
            p_both_ge_k = ((max_val - k + 1) / max_val) ** 2
            p_both_ge_kp1 = ((max_val - k) / max_val) ** 2
            p_min_equals_k = p_both_ge_k - p_both_ge_kp1
            penalty_sum += k * p_min_equals_k
        
        # Bonus (максимум двух)
        bonus_sum = 0
        for k in range(1, max_val + 1):
            p_both_le_k = (k / max_val) ** 2
            p_both_le_km1 = ((k - 1) / max_val) ** 2
            p_max_equals_k = p_both_le_k - p_both_le_km1
            bonus_sum += k * p_max_equals_k
        
        normal_expectations.append(normal)
        penalty_expectations.append(penalty_sum)
        bonus_expectations.append(bonus_sum)
    
    ax.plot(max_values, normal_expectations, 'b-o', linewidth=2, 
            markersize=6, label='Нормальный', alpha=0.8)
    ax.plot(max_values, penalty_expectations, 'r-s', linewidth=2, 
            markersize=6, label='Штраф', alpha=0.8)
    ax.plot(max_values, bonus_expectations, 'g-^', linewidth=2, 
            markersize=6, label='Преимущество', alpha=0.8)
    
    ax.set_title('Влияние штрафа/преимущества на матожидание', fontsize=16)
    ax.set_xlabel('Максимальное значение кубика (max)', fontsize=14)
    ax.set_ylabel('Матожидание', fontsize=14)
    ax.legend(fontsize=12)
    ax.grid(True, alpha=0.3)
    ax.set_xscale('log')
    
    # Отметим D6 и D100
    ax.axvline(x=6, color='gray', linestyle='--', alpha=0.5)
    ax.text(6.2, min(penalty_expectations), 'D6', fontsize=10)
    
    ax.axvline(x=100, color='gray', linestyle='--', alpha=0.5)
    ax.text(102, min(penalty_expectations), 'D100', fontsize=10)
    
    plt.tight_layout()
    plt.savefig('expectation_chart.png', dpi=300, bbox_inches='tight')
    plt.show()

if __name__ == "__main__":
    main()