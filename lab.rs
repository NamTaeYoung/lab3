use std::io;

fn main() {
    let mut input = String::new();

    // 행렬의 크기 입력
    println!("행렬의 행 개수를 입력하세요: ");
    io::stdin().read_line(&mut input).unwrap();
    let rows: usize = input.trim().parse().unwrap();
    input.clear();

    println!("행렬의 열 개수를 입력하세요: ");
    io::stdin().read_line(&mut input).unwrap();
    let cols: usize = input.trim().parse().unwrap();

    // 두 행렬과 결과 행렬 선언
    let mut matrix1: Vec<Vec<i32>> = vec![vec![0; cols]; rows];
    let mut matrix2: Vec<Vec<i32>> = vec![vec![0; cols]; rows];
    let mut result: Vec<Vec<i32>> = vec![vec![0; cols]; rows];

    // 첫 번째 행렬 입력
    println!("첫 번째 행렬의 값을 입력하세요:");
    for i in 0..rows {
        for j in 0..cols {
            println!("첫 번째 행렬 [{}][{}]:", i, j);
            input.clear();
            io::stdin().read_line(&mut input).unwrap();
            matrix1[i][j] = input.trim().parse().unwrap();
        }
    }

    // 두 번째 행렬 입력
    println!("두 번째 행렬의 값을 입력하세요:");
    for i in 0..rows {
        for j in 0..cols {
            println!("두 번째 행렬 [{}][{}]:", i, j);
            input.clear();
            io::stdin().read_line(&mut input).unwrap();
            matrix2[i][j] = input.trim().parse().unwrap();
        }
    }

    // 두 행렬의 합 계산
    for i in 0..rows {
        for j in 0..cols {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    // 결과 행렬 출력
    println!("두 행렬의 합은 다음과 같습니다:");
    for i in 0..rows {
        for j in 0..cols {
            print!("{} ", result[i][j]);
        }
        println!();
    }
}