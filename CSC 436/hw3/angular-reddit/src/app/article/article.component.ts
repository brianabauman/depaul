import {
  Component,
  OnInit,
  Input,
  HostBinding
} from '@angular/core';
import { Article } from './article.model';
import { FlagService } from '../flag.service';

@Component({
  selector: 'app-article',
  templateUrl: './article.component.html',
  styleUrls: ['./article.component.css'],
  host: {
    class: 'row'
  }
})

export class ArticleComponent implements OnInit {
  @Input() article: Article;
  @Input('articles') articles: Article[];

  constructor(private flagService: FlagService) {
  }

  voteUp(): boolean {
    this.article.votes += 1;
    return false;
  }

  voteDown(): boolean {
    this.article.votes -= 1;
    return false;
  }

  flagArticle() {
    let minScore = this.articles[0].votes;
    for (var i = 1; i < this.articles.length; i++) {
      if (this.articles[i].votes < minScore) {
        minScore = this.articles[i].votes;
      }
    }

    this.flagService.flagArticle(this.article, minScore);
  }

  ngOnInit() {
  }
}
