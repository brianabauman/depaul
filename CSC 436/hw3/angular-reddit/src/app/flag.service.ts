import { Injectable } from '@angular/core';
import { Article } from './article/article.model';

@Injectable({
  providedIn: 'root'
})
export class FlagService {

  constructor() { }
  
  flagArticle(article: Article, minScore: number) {
      article.votes = minScore - 1;
  }
}
