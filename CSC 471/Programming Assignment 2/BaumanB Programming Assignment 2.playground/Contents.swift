// Brian Bauman
// CSC 471
// Programming Assignment 2

// 2.

// (a)
func rank(of x: Int, in arr: [Int]) -> Int {
    var high = arr.count - 1;
    var low = 0;
    var mid = (low + high) / 2;
    
    while low <= high {
        if x == arr[mid] {
            return mid;
        } else if x < arr[mid] {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
        mid = (low + high) / 2;
    }

    return -1;
}

// (b)
var testArray: [Int] = [1, 2, 3, 4, 5, 6, 7, 8];
print(rank(of: 1, in: testArray));
print(rank(of: 2, in: testArray));
print(rank(of: 4, in: testArray));
print(rank(of: 8, in: testArray));
print(rank(of: 9, in: testArray));
print();

// 3.

// (a)
class Fraction {
    var numerator: Int = 0;
    var denominator: Int = 0;
    
    init() {}
    init(_ numerator: Int, over denominator: Int) {
        self.numerator = numerator;
        self.denominator = denominator;
    }

    func print() {
        Swift.print("\(numerator)/\(denominator)");
    }
    
    func toDouble() -> Double {
        return Double(numerator) / Double(denominator);
    }
    
    func setTo(_ numerator: Int, over denominator: Int) {
        self.numerator = numerator;
        self.denominator = denominator;
    }
    
    func reduce() {
        let sign = (self.numerator >= 0) ? 1 : -1;
        
        var u = self.numerator * sign;
        var v = self.denominator;
        var r: Int;
        
        while v != 0 {
            r = u % v;
            u = v;
            v = r;
        }
        
        self.numerator /= u;
        self.denominator /= u;
    }
    
    func add(_ f: Fraction) -> Fraction {
        let result = Fraction();
        
        result.numerator = (self.numerator * f.denominator) + (self.denominator * f.numerator);
        result.denominator = self.denominator * f.denominator;
        
        result.reduce();
        return result;
    }
    
    func subtract(_ f: Fraction) -> Fraction {
        let result = Fraction();
        
        result.numerator = (self.numerator * f.denominator) - (self.denominator * f.numerator);
        result.denominator = self.denominator * f.denominator;
        
        result.reduce();
        return result;
    }
    
    func multiply(by f: Fraction) -> Fraction {
        let result = Fraction();
        
        result.numerator = self.numerator * f.numerator;
        result.denominator = self.denominator * f.denominator;
        
        result.reduce();
        return result;
    }
    
    func divide(by f: Fraction) -> Fraction {
        if f.numerator == 0 { return Fraction(0, over: 0); }
        
        let result = Fraction();
        
        result.numerator = self.numerator * f.denominator;
        result.denominator = self.denominator * f.numerator;
        
        result.reduce();
        return result;
    }
}

// (b)
print("Adding 1/2 to 3/4...");
var x = Fraction(1, over: 2);
var y = Fraction(3, over: 4);
x.add(y).print();

print("Subtracting 1/2 from 1/4...");
x = Fraction(1, over: 4);
y = Fraction(1, over: 2);
x.subtract(y).print();

print("Multiplying 1/3 by 2/3...");
x = Fraction(1, over: 3);
y = Fraction(2, over: 3);
x.multiply(by: y).print();

print("Dividing 2/3 by 3/4...");
x = Fraction(2, over: 3);
y = Fraction(3, over: 4);
x.divide(by: y).print();
