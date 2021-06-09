//
//  ViewController.swift
//  BaumanB Calculator
//
//  Created by Brian Bauman on 2/3/19.
//  Copyright © 2019 Brian Bauman. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    var plusPressedInd: Bool = false;
    var equalsPressedInd: Bool = false;
    var firstNumberText: String = "";
    var secondNumberText: String = "";
    
    @IBOutlet weak var label: UILabel!;
    
    @IBAction func numberPressed(_ sender: UIButton) {
        
        let inputValueText: String = sender.currentTitle!;
        
        if (equalsPressedInd && !plusPressedInd) {
            equalsPressedInd = false;
            firstNumberText = "";
        }
        
        if (plusPressedInd) {
            secondNumberText = secondNumberText + inputValueText;
            label.text = secondNumberText;
        } else {
            firstNumberText = firstNumberText + inputValueText;
            label.text = firstNumberText;
        }
    }

    @IBAction func plusPressed() {
        plusPressedInd = true;
    }
    
    @IBAction func equalsPressed() {
        equalsPressedInd = true;
        
        if (plusPressedInd) {
            
            let firstNumber: Int = Int(firstNumberText) ?? 0;
            let secondNumber: Int = Int(secondNumberText) ?? 0;
            
            label.text = String(firstNumber + secondNumber);
            
            firstNumberText = label.text ?? "";
            secondNumberText = "";
            
            plusPressedInd = false;
        }
    }
}

