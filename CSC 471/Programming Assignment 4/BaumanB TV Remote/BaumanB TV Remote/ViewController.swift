//
//  ViewController.swift
//  BaumanB TV Remote
//
//  Created by Brian Bauman on 2/11/19.
//  Copyright © 2019 Brian Bauman. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var tvPowerLabel: UILabel?;
    @IBOutlet weak var speakerVolumeLabel: UILabel?;
    @IBOutlet weak var currentChannelLabel: UILabel?;
    
    @IBOutlet weak var tvPowerSwitch: UISwitch?;
    @IBOutlet weak var volumeSlider: UISlider?;
    @IBOutlet weak var zeroButton: UIButton?;
    @IBOutlet weak var oneButton: UIButton?;
    @IBOutlet weak var twoButton: UIButton?;
    @IBOutlet weak var threeButton: UIButton?;
    @IBOutlet weak var fourButton: UIButton?;
    @IBOutlet weak var fiveButton: UIButton?;
    @IBOutlet weak var sixButton: UIButton?;
    @IBOutlet weak var sevenButton: UIButton?;
    @IBOutlet weak var eightButton: UIButton?;
    @IBOutlet weak var nineButton: UIButton?;
    @IBOutlet weak var channelUpButton: UIButton?;
    @IBOutlet weak var channelDownButton: UIButton?;
    @IBOutlet weak var favoriteChannelControl: UISegmentedControl?;

    var firstDigitPressed: Bool = false;
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        //reset settings
        if let tvPowerLabel = tvPowerLabel,
           let speakerVolumeLabel = speakerVolumeLabel,
           let currentChannelLabel = currentChannelLabel,
           let tvPowerSwitch = tvPowerSwitch,
           let volumeSlider = volumeSlider,
           let zeroButton = zeroButton,
           let oneButton = oneButton,
           let twoButton = twoButton,
           let threeButton = threeButton,
           let fourButton = fourButton,
           let fiveButton = fiveButton,
           let sixButton = sixButton,
           let sevenButton = sevenButton,
           let eightButton = eightButton,
           let nineButton = nineButton,
           let channelUpButton = channelUpButton,
           let channelDownButton = channelDownButton,
           let favoriteChannelControl = favoriteChannelControl {
            tvPowerLabel.text = "Off";
            speakerVolumeLabel.text = "00";
            currentChannelLabel.text = "00"
            tvPowerSwitch.isOn = false;
            volumeSlider.value = 0;
            volumeSlider.isEnabled = false;
            zeroButton.isEnabled = false;
            oneButton.isEnabled = false;
            twoButton.isEnabled = false;
            threeButton.isEnabled = false;
            fourButton.isEnabled = false;
            fiveButton.isEnabled = false;
            sixButton.isEnabled = false;
            sevenButton.isEnabled = false;
            eightButton.isEnabled = false;
            nineButton.isEnabled = false;
            channelUpButton.isEnabled = false;
            channelDownButton.isEnabled = false;
            favoriteChannelControl.isEnabled = false;
            favoriteChannelControl.selectedSegmentIndex = 0;
        }
    }
    
    @IBAction func powerToggleDidChange(sender: UISwitch) {
        if let tvPowerLabel = tvPowerLabel,
           let volumeSlider = volumeSlider,
           let zeroButton = zeroButton,
           let oneButton = oneButton,
           let twoButton = twoButton,
           let threeButton = threeButton,
           let fourButton = fourButton,
           let fiveButton = fiveButton,
           let sixButton = sixButton,
           let sevenButton = sevenButton,
           let eightButton = eightButton,
           let nineButton = nineButton,
           let channelUpButton = channelUpButton,
           let channelDownButton = channelDownButton,
           let favoriteChannelControl = favoriteChannelControl {
            if sender.isOn {
                tvPowerLabel.text = "On";
                volumeSlider.isEnabled = true;
                zeroButton.isEnabled = true;
                oneButton.isEnabled = true;
                twoButton.isEnabled = true;
                threeButton.isEnabled = true;
                fourButton.isEnabled = true;
                fiveButton.isEnabled = true;
                sixButton.isEnabled = true;
                sevenButton.isEnabled = true;
                eightButton.isEnabled = true;
                nineButton.isEnabled = true;
                channelUpButton.isEnabled = true;
                channelDownButton.isEnabled = true;
                favoriteChannelControl.isEnabled = true;
            } else {
                tvPowerLabel.text = "Off";
                volumeSlider.isEnabled = false;
                zeroButton.isEnabled = false;
                oneButton.isEnabled = false;
                twoButton.isEnabled = false;
                threeButton.isEnabled = false;
                fourButton.isEnabled = false;
                fiveButton.isEnabled = false;
                sixButton.isEnabled = false;
                sevenButton.isEnabled = false;
                eightButton.isEnabled = false;
                nineButton.isEnabled = false;
                channelUpButton.isEnabled = false;
                channelDownButton.isEnabled = false;
                favoriteChannelControl.isEnabled = false;
            }
        }
    }
    
    @IBAction func volumeSliderDidChange(sender: UISlider) {
        if let speakerVolumeLabel = speakerVolumeLabel {
            
            speakerVolumeLabel.text = String(Int(sender.value * 100));
        }
    }
    
    @IBAction func channelNumberWasPressed(sender: UIButton) {
        if let number = sender.currentTitle,
           let currentChannelLabel = currentChannelLabel,
           var currentChannelText = currentChannelLabel.text {
            if firstDigitPressed {
                currentChannelLabel.text = currentChannelText + number;
                firstDigitPressed = false;
            } else {
                currentChannelLabel.text = number;
                firstDigitPressed = true;
            }
        }
    }
    
    @IBAction func channelUpWasPressed(sender: UIButton) {
        if let currentChannelLabel = currentChannelLabel,
           let text = currentChannelLabel.text,
           let number = Int(text) {
            if number < 98 {
                currentChannelLabel.text = String(format: "%02d", number + 1);
            }
        }
    }
    
    @IBAction func channelDownWasPressed(sender: UIButton) {
        if let currentChannelLabel = currentChannelLabel,
           let text = currentChannelLabel.text,
           let number = Int(text) {
            if number > 0 {
                currentChannelLabel.text = String(format: "%02d", number - 1);
            }
        }
    }
    
    @IBAction func favoriteChannelWasChanged(sender: UISegmentedControl) {
        var channel = "";
        switch sender.selectedSegmentIndex {
        case 0:
            channel = "07";
        case 1:
            channel = "02";
        case 2:
            channel = "21";
        case 3:
            channel = "32";
        default:
            //do nothing
            channel = "00";
        }
        
        if let currentChannelLabel = currentChannelLabel {
            currentChannelLabel.text = channel;
        }
    }
}

