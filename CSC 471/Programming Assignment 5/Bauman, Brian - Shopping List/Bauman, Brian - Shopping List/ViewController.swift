//
//  ViewController.swift
//  Bauman, Brian - Shopping List
//
//  Created by Brian Bauman on 2/18/19.
//  Copyright © 2019 Brian Bauman. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    
    @IBOutlet weak var listLabel: UILabel?;
    @IBOutlet weak var descriptionTextField: UITextField?;
    @IBOutlet weak var quantityTextField: UITextField?;
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    @IBAction func newItemButtonPressed() {
        if let descriptionTextField = descriptionTextField {
            descriptionTextField.text = "";
        }
        
        if let quantityTextField = quantityTextField {
            quantityTextField.text = "";
        }
    }
    
    @IBAction func newListButtonPressed() {
        if let listLabel = listLabel {
            listLabel.text = "No item";
        }
    }
    
    @IBAction func addButtonPressed() {
        var description = "";
        var quantity = "";
        
        if let descriptionTextField = descriptionTextField {
            description = descriptionTextField.text!;
        }
        
        if let quantityTextField = quantityTextField {
            quantity = quantityTextField.text!;
        }
        
        if Int(quantity) != nil && description != "" {
            if let listLabel = listLabel {
                if listLabel.text! == "No item" {
                    listLabel.text = "\(quantity)x \(description)";
                } else {
                    listLabel.text = listLabel.text! + "\r\(quantity)x \(description)";
                }
            }
            
            newItemButtonPressed();
        } else {
            let alertController = UIAlertController(title: "Invalid data", message: "Please enter a valid description and quantity.", preferredStyle: .alert);
            let cancelAction = UIAlertAction(title: "OK", style: .cancel, handler: nil);
            alertController.addAction(cancelAction);
            present(alertController, animated: true, completion: nil);
        }
    }
    
    @IBAction func editEnded(_ sender: UITextField) {
        sender.resignFirstResponder();
    }
    
    @IBAction func containerViewPressed(_ sender: UIControl) {
        descriptionTextField?.resignFirstResponder();
        quantityTextField?.resignFirstResponder();
    }
}
