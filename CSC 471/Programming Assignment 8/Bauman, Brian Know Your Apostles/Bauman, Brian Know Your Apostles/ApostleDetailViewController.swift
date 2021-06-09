//
//  ApostleDetailViewController.swift
//  Bauman, Brian Know Your Apostles
//
//  Created by Brian Bauman on 3/12/19.
//  Copyright © 2019 Brian Bauman. All rights reserved.
//

import UIKit

class ApostleDetailViewController: UIViewController {

    @IBOutlet weak var nameLabel: UILabel!
    @IBOutlet weak var nicknameLabel: UILabel!
    @IBOutlet weak var funFactLabel: UILabel!
    @IBOutlet weak var descriptionLabel: UILabel!
    @IBOutlet weak var imageView: UIImageView!
    
    var apostle: Apostle?
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }
    
    override func viewWillAppear(_ animated: Bool) {
        if let a = apostle {
            nameLabel.text = a.name
            nicknameLabel.text = a.nickname
            funFactLabel.text = a.funFact
            descriptionLabel.text = a.description
            imageView.image = UIImage(named: a.imageName)
        }
    }
    
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
    }
    */
}
